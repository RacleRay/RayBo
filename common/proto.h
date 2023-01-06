/*************************************************************************
    > File Name: proto.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#ifndef _PROTO_H
#define _PROTO_H

/*
对应 proto/message_define.proto 中消息格式设计
*/
#define REG_REQ 401
#define REG_RSP 402

#define LOGIN_REQ 101
#define LOGIN_RSP 102
#define LOGOUT_REQ 103
#define LOGOUT_RSP 104

#define ADD_FRIEND_REQ 201
#define ADD_FRIEND_RSP 202
#define DEL_FRIEND_REQ 203
#define DEL_FRIEND_RSP 204

#define GET_PHOTO_REQ 301
#define GET_PHOTO_RSP 302
#define GET_MESSAGE_LIST_REQ 303
#define GET_MESSAGE_LIST_RSP 304
#define PUBLISH_MESSAGE_REQ 305
#define PUBLISH_MESSAGE_RSP 306

#define SERVER_RESTART 601
#define SERVER_SHUTDOWN 602

/* 进程间通信状态 */
#define GET_USER_ID_REQ 1001
#define GET_USER_ID_RSP 1002
#define CREATE_USER_REQ 1003
#define CREATE_USER_RSP 1004
#define LOGIN_CHECK_REQ 1005
#define LOGIN_CHECK_RSP 1006
#define CHECH_EXIST_REQ 1007
#define CHECK_EXIST_RSP 1008

#endif