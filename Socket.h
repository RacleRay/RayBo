/*************************************************************************
    > File Name: Socket.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _SOCKET_H
#define _SOCKET_H

#include "Config.h"
#include "common/macro.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace raybo {

#define USE_SOCKET_CHECK if (use_socket==0) { return 0; }

#define SLEP 0
#define RECV 1
#define SEND 2

class RayBoSocket {
private:
    int use_socket;
    int rs_flag;     // SLEP or RECV or SEND

public:
    Config config;

    int                server_sock;
    struct sockaddr_in server_addr;
    int                client_sock;
    struct sockaddr_in client_addr;
    int                accept_flag;
    char               recv_buffer[MAX_BUFFER_SIZE];
    char               send_buffer[MAX_BUFFER_SIZE];
    int                Init();
    int                SocketInit();
    int                SocketAccept();
    int                SocketCheckRecv();
    int                SocketSend(int send_size);
    int                ClientClose();
    int                ServerClose();
    int                ClientSocketInit();
    int                show_send_buffer(int size);
    int                show_recv_buffer(int size);
};
}  // namespace raybo


#endif
