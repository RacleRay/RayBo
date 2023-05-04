/*************************************************************************
    > File Name: Socket.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// type = 1 读取server config，2 读取client config
int raybo::RayBoSocket::Init(int type) {
    rs_flag     = SLEP;
    accept_flag = 0;

    config.ReadConfig(type);
    use_socket = config.use_socket();

    DBG(GREEN " --- Socket init --- \n" NONE);
}

int raybo::RayBoSocket::SocketInit() {
    USE_SOCKET_CHECK

    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(config.socket_port());
    server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
    DBG(YELLOW "> socket: %d \n" NONE, server_sock);

    int state = -1;
    state = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    DBG(YELLOW "> bind: %d \n" NONE, state);
    state = listen(server_sock, MAX_LISTEN_PORTS);
    DBG(YELLOW "> listen: %d \n" NONE, state);

    return 0;
}

// 使用的是client config文件
int raybo::RayBoSocket::ClientSocketInit() {
    USE_SOCKET_CHECK

    client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
    server_addr.sin_port        = htons(config.socket_port());

    int conn_ret = connect(client_sock, (struct sockaddr*)&server_addr,
                           sizeof(server_addr));
    if (conn_ret < 0) {
        return conn_ret;
    }
    accept_flag = 1;
    return 0;
}

int raybo::RayBoSocket::SocketAccept() {
    USE_SOCKET_CHECK

    if (accept_flag == 1) return 0;  // server已有连接

    struct sockaddr_in client_addr;

    socklen_t client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

    accept_flag = 1;
    return 0;
}

int raybo::RayBoSocket::SocketCheckRecv() {
    USE_SOCKET_CHECK

    // 没有连接
    if (accept_flag == 0) return -1;
    // 已经接收到消息，且还未处理
    if (rs_flag == RECV) return 0;

    DBG(GREEN " recving\n" NONE);
    int ret = recv(client_sock, recv_buffer, MAX_BUFFER_SIZE, 0);
    DBG(GREEN " recv ok\n" NONE);
    if (ret > 0) {
        rs_flag = RECV;
        return ret;
    }
    else {
        return -1;
    }
    return 0;
}

int raybo::RayBoSocket::SocketSend(int fd, int send_size) {
    USE_SOCKET_CHECK
    if (send_size >= MAX_BUFFER_SIZE) {
        DBG(RED "!!! send_size > MAX_BUFFER_SIZE\n" NONE);
        ClientClose();
        return -1;
    }

    int ret = send(fd, send_buffer, send_size, 0);
    memset(send_buffer, 0, send_size);
    if (ret < 0) {
        DBG(RED "!!! socket send error\n" NONE);
        ClientClose();
        return -1;
    }
    rs_flag = SEND;  // 完成消息发送

    return 0;
}

int raybo::RayBoSocket::ClientClose() {
    USE_SOCKET_CHECK

    close(client_sock);
    accept_flag = 0;  // 无连接
    return 0;
}

int raybo::RayBoSocket::ServerClose() {
    USE_SOCKET_CHECK

    close(server_sock);
    return 0;
}

/*调试使用*/
int raybo::RayBoSocket::show_send_buffer(int size) {
    for (int i = 0; i < size; i++) {
        // 查看当前第i个字节的 l4：低4位 h4: 高4位
        int l4 = send_buffer[i] & 0x000f;
        int h4 = (send_buffer[i] >> 4) & 0x000f;

        // 逐个查看每一个位
        int l0 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l1 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l2 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l3 = l4 & 0x0001;
        l3     = l4 & 0x0001;

        int h0 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h1 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h2 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h3 = h4 & 0x0001;

        printf("%02x %d%d%d%d %d%d%d%d %3d", send_buffer[i], h3, h2, h1, h0, l3,
               l2, l1, l0, send_buffer[i]);
        if ('0' <= send_buffer[i] && send_buffer[i] <= '9')
            printf("'%c'", send_buffer[i]);
        if ('A' <= send_buffer[i] && send_buffer[i] <= 'Z')
            printf("'%c'", send_buffer[i]);
        if ('a' <= send_buffer[i] && send_buffer[i] <= 'z')
            printf("'%c'", send_buffer[i]);
        printf("\n");
    }
    return 0;
}

int raybo::RayBoSocket::show_recv_buffer(int size) {
    for (int i = 0; i < size; i++) {
        int l4 = recv_buffer[i] & 0x000f;
        int h4 = (recv_buffer[i] >> 4) & 0x000f;

        int l0 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l1 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l2 = l4 & 0x0001;
        l4     = l4 >> 1;
        int l3 = l4 & 0x0001;

        int h0 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h1 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h2 = h4 & 0x0001;
        h4     = h4 >> 1;
        int h3 = h4 & 0x0001;
        printf("%02x %d%d%d%d %d%d%d%d %3d ", recv_buffer[i], h3, h2, h1, h0,
               l3, l2, l1, l0, recv_buffer[i]);
        if ('0' <= recv_buffer[i] && recv_buffer[i] <= '9')
            printf("'%c'", recv_buffer[i]);
        if ('A' <= recv_buffer[i] && recv_buffer[i] <= 'Z')
            printf("'%c'", recv_buffer[i]);
        if ('a' <= recv_buffer[i] && recv_buffer[i] <= 'z')
            printf("'%c'", recv_buffer[i]);
        printf("\n");
    }
    return 0;
}