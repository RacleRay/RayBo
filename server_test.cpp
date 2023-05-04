/*************************************************************************
    > File Name: server.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "common/macro.h"
#include "common/proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    // read config

    // server on
    int server_on = 1;
    while (server_on) {
        // prepare user manager, relation manager, message manager, photo
        // manager

        // get command type, designed in "common/proto.h"
        int cmd_id = -1;
        // get from message header.

        // sleep when waiting for works.
        if (cmd_id < 0) {
            usleep(SLEEP_TIME_MICS);
            continue;
        }

        // deal with cmd_id which means command type.
        DBG(GREEN "--- cmd_id : %d --- \n" NONE, cmd_id);

        switch (cmd_id) {
        case REG_REQ: {
            // 注册流程

        } break;
        case GET_USER_ID_RSP: {
            // 获取用户id流程

        } break;
        case CREATE_USER_RSP: {
            // 创建用户流程

        } break;
        case LOGIN_REQ: {
            // 登录流程

        } break;
        case ADD_FRIEND_REQ: {
            // 添加好友流程

        } break;
        case PUBLISH_MESSAGE_REQ: {
            // 发布动态流程

        } break;
        case GET_PHOTO_REQ: {
            // 拉取消息快照流程

        } break;
        case GET_MESSAGE_LIST_REQ: {
            // 拉取动态消息流程

        } break;
        case DEL_FRIEND_REQ: {
            // 删除好友流程

        } break;
        case LOGOUT_REQ: {
            // 登出流程

        } break;
        case SERVER_SHUTDOWN: {
            // 关闭服务
            server_on = 0;
        }
        default:
            break;
        }
    }

    // shutdown workers

    return 0;
}