/*************************************************************************
    > File Name: user_server.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "BusManager.h"
#include "Database.h"
#include "UserManager.h"
#include "common/proto.h"
#include "common/return_state.h"
#include "proto/message_define.pb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 使用共享内存进行用户分流，提高并发性能，也即单独建立UserServer的进程
// 进程间使用共享内存通信。

BusManager             bus;
raybo::UserManager     user_svr;
raybo::Database        db_svr;
raybo::ServerToUserReq inner_req;
raybo::UserToServerRsp inner_rsp;
int                    user_svr_id = 0;  // 1 or 2


void MAKE_RSP_HEAD(int cmd_id) {
    inner_rsp.Clear();
    inner_rsp.mutable_header()->set_ver(1);
    inner_rsp.mutable_header()->set_cmd_type(cmd_id + 1);
}

void BUS_SEND_RSP(int from, int to) {
    inner_rsp.SerializeToArray(bus.send_buffer, inner_rsp.ByteSize());
    DBG("--- [debug] bus send message:\n ");
    std::string debug_message = inner_rsp.Utf8DebugString();
    DBG("%s\n", debug_message.c_str());
    int ret = bus.Send(from, to, bus.send_buffer, inner_rsp.ByteSize());
    DBG("send_ret: %d\n", ret);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        DBG("Usage: user_svr <svr_id>");
        return 0;
    }

    sscanf(argv[1], "%d", &user_svr_id);
    bus.Init();
    db_svr.Init();
    user_svr.Start(&db_svr);

    int server_on = 1;
    while (server_on) {
        int time_now  = time(NULL);
        // 从共享内存 bus channel 中读取内容，返回与user_svr相连的用户请求server
        int check_bus = bus.CheckRecv(user_svr_id);
        if (check_bus != -1) {
            inner_req.ParseFromArray(bus.Recv(check_bus, user_svr_id),
                                     bus.RecvSize(check_bus, user_svr_id));
            DBG("--- [debug] bus recv message: \n");
            std::string debug_message = inner_req.Utf8DebugString();
            DBG(" %s \n ", debug_message.c_str());
            bus.Clear(check_bus, user_svr_id);  // 用户通信的server和user server的bus channel

            int cmd_id = inner_req.header().cmd_type();
            switch (cmd_id) {
            case GET_USER_ID_REQ: {
                MAKE_RSP_HEAD(cmd_id);
                int user_id = user_svr.GetUserIdByUserName(
                    inner_req.get_user_id().user_name().c_str());
                if (user_id != USER_NOT_EXIST) {
                    inner_rsp.mutable_get_user_id()->set_ret(USER_EXIST);
                }
                else {
                    inner_rsp.mutable_get_user_id()->set_ret(USER_NOT_EXIST);
                    inner_rsp.mutable_get_user_id()->set_user_id(user_svr.idle_id());
                }
                BUS_SEND_RSP(user_svr_id, check_bus);  // user_ser 与 用户连接server通信
            } break;
            case CREATE_USER_REQ: {
                MAKE_RSP_HEAD(cmd_id);
                int user_id = user_svr.CreateUser(
                    inner_req.create_user().user_name().c_str(),
                    inner_req.create_user().password().c_str(),
                    inner_req.create_user().from(),
                    time_now);
                if (user_id == USER_EXIST) {
                    inner_rsp.mutable_create_user()->set_ret(USER_EXIST);
                    inner_rsp.mutable_create_user()->set_user_id(user_id);
                } else if (user_id == USER_TOO_MUCH) {
                    inner_rsp.mutable_create_user()->set_ret(USER_TOO_MUCH);
                    DBG("--- [debug] User too much \n");
                } else {
                    inner_rsp.mutable_create_user()->set_ret(SUCCESS);
                    inner_rsp.mutable_create_user()->set_user_id(user_id);
                }
                BUS_SEND_RSP(user_svr_id, check_bus);
            } break;
            case LOGIN_CHECK_REQ: {
                MAKE_RSP_HEAD(cmd_id);
                int ret_state = user_svr.LoginCheck(
                    inner_req.login_check().user_name().c_str(),
                    inner_req.login_check().password().c_str()
                );
                inner_rsp.mutable_login_check()->set_ret(ret_state);
                BUS_SEND_RSP(user_svr_id, check_bus);
            } break;
            case CHECH_EXIST_REQ: {
                MAKE_RSP_HEAD(cmd_id);
                BUS_SEND_RSP(user_svr_id, check_bus);
            } break;
            default:
                break;
            }
        }
    }
    bus.Detach();
    return 0;
}