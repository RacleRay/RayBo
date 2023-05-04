/*************************************************************************
    > File Name: client_test.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "Socket.h"
#include "common/proto.h"
#include "proto/message_define.pb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


#define DEBUG 1

#define GOTO_BEGIN                                                             \
    if (ret == 0) {                                                            \
        phase = 1;                                                             \
    }
#define GOTO_NEXT                                                              \
    if (ret == 0) {                                                            \
        phase++;                                                               \
    }
#define GOTO_LOGIN                                                             \
    if (ret == 0) {                                                            \
        phase = 5;                                                             \
    }
#define GET_OUT                                                                \
    if (ret == 0) {                                                            \
        phase = 999;                                                           \
    }
#define WAIT_RSP_GO_NEXT                                                       \
    ret = RecvRsp();                                                           \
    GOTO_NEXT
#define WAIT_RSP_GO_LOGIN                                                      \
    ret = RecvRsp();                                                           \
    GOTO_LOGIN
#define WAIT_RSP_GO_BEGIN                                                      \
    ret = RecvRsp();                                                           \
    GOTO_BEGIN
#define WAIT_RSP_GET_OUT                                                       \
    ret = RecvRsp();                                                           \
    GET_OUT
#define CHECK_SERVER_ON                                                        \
    if (ret < 0) {                                                             \
        DBG("Server Not Ready\n");                                             \
        return 0;                                                              \
    }

raybo::CommonReq common_req;
raybo::CommonRsp common_rsp;

raybo::RayBoSocket sock;
int                saved_user_id = 0;


int Register(const char* user_name, const char* password) {
    DBG("Registing.");
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(REG_REQ);
    common_req.mutable_reg_req()->set_user_name(user_name);
    common_req.mutable_reg_req()->set_password(password);
    common_req.mutable_reg_req()->set_from(1);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int Login(const char* user_name, const char* password) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(LOGIN_REQ);
    common_req.mutable_login_req()->set_user_name(user_name);
    common_req.mutable_login_req()->set_password(password);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int Logout(int user_id) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(LOGOUT_REQ);
    common_req.mutable_logout_req()->set_user_id(user_id);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int AddFriend(int user_id, int other_id) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(ADD_FRIEND_REQ);
    common_req.mutable_add_friend_req()->set_user_id(user_id);
    common_req.mutable_add_friend_req()->set_other_id(other_id);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int DelFriend(int user_id, int other_id) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(DEL_FRIEND_REQ);
    common_req.mutable_del_friend_req()->set_user_id(user_id);
    common_req.mutable_del_friend_req()->set_other_id(other_id);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int PublishMessage(int user_id, const char* content) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(PUBLISH_MESSAGE_REQ);
    common_req.mutable_publish_message_req()->set_user_id(user_id);
    common_req.mutable_publish_message_req()->set_content(content);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int GetPhoto(int user_id) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
    common_req.mutable_get_photo_req()->set_user_id(user_id);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

int GetMessageList(int user_id) {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(GET_MESSAGE_LIST_REQ);
    common_req.mutable_get_message_list_req()->set_user_id(user_id);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

// 管理员
int ShutDown() {
    common_req.Clear();
    common_req.mutable_header()->set_ver(1);
    common_req.mutable_header()->set_cmd_type(SERVER_SHUTDOWN);
    common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());
    int ret = sock.SocketSend(sock.client_sock, common_req.ByteSize());
    return ret;
}

// 检查查询结果
int RecvRsp() {
    int ret = sock.SocketCheckRecv();
    if (ret > 0) {
        common_rsp.ParseFromArray(sock.recv_buffer, 10240);
        int cmd_type = common_rsp.header().cmd_type();
        if (DEBUG == 0) return 0;
        switch (cmd_type) {
        case REG_RSP:
            DBG("Receive Reg Rsp\n");
            DBG("ret    : %d\n", common_rsp.reg_rsp().ret());
            DBG("user_id: %d\n", common_rsp.reg_rsp().user_id());
            break;
        case LOGIN_RSP:
            DBG("Receive Login Rsp\n");
            DBG("ret    : %d\n", common_rsp.login_rsp().ret());
            DBG("user_id: %d\n", common_rsp.login_rsp().user_id());
            if (saved_user_id == 0) {
                saved_user_id = common_rsp.login_rsp().user_id();
            }
            break;
        case ADD_FRIEND_RSP:
            DBG("Receive AddFriend Rsp\n");
            DBG("ret    : %d\n", common_rsp.add_friend_rsp().ret());
            break;
        case DEL_FRIEND_RSP:
            DBG("Receive DelFriend Rsp\n");
            DBG("ret    : %d\n", common_rsp.del_friend_rsp().ret());
            break;
        case PUBLISH_MESSAGE_RSP:
            DBG("Receive PublishMessage Rsp\n");
            DBG("ret    : %d\n", common_rsp.publish_message_rsp().ret());
            break;
        case GET_PHOTO_RSP:
            DBG("Receive GetPhoto Rsp\n");
            DBG("ret    : %d\n", common_rsp.get_photo_rsp().ret());
            DBG("update : %d\n",
                common_rsp.get_photo_rsp().last_publisher_id());
            break;
        case GET_MESSAGE_LIST_RSP: {
            DBG("Receive GetMessageList Rsp\n");
            DBG("ret    : %d\n", common_rsp.get_message_list_rsp().ret());
            int message_count =
                common_rsp.get_message_list_rsp().message_list_size();
            DBG("count  : %d\n",
                common_rsp.get_message_list_rsp().message_list_size());
            for (int i = 0; i < message_count; i++) {
                DBG("%6d : %s\n",
                    common_rsp.get_message_list_rsp()
                        .message_list(i)
                        .publisher_id(),
                    common_rsp.get_message_list_rsp()
                        .message_list(i)
                        .content()
                        .c_str());
            }
        } break;
        default:
            break;
        }
    }
    else {
        return -1;
    }
    return 0;
}

int main() {
    int ret;
    ret = sock.Init(2);
    ret = sock.ClientSocketInit();
    CHECK_SERVER_ON
    int client_on = 1;
    int phase     = 1;
    while (client_on) {
        switch (phase) {
        case 1:
            DBG("test regist. \n");
            ret = Register("racle", "666666");
            GOTO_NEXT
            break;
        case 2:
            DBG("test response. \n");
            WAIT_RSP_GO_NEXT
            break;
        default:
            ret = Logout(saved_user_id);
            // ret = ShutDown();
            // GOTO_NEXT
            client_on = 0;
            break;
        }
    }
    sock.ClientClose();
    return 0;
}