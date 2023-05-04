/*************************************************************************
    > File Name: Config.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Config.h"

int raybo::Config::ReadConfig(int type) {
    FILE* fp = NULL;
    if (type == 1)
        fp = fopen("server_config.ini", "r");
    else
        fp = fopen("client_config.ini", "r");
    if (fp == NULL) {
        return -1;
    }
    while (1) {
        char buffer[256];
        if (fscanf(fp, "%s", buffer) == EOF) {
            break;
        }
        if (strstr(buffer, "use_socket") != NULL) {
            sscanf(buffer, "use_socket=%d", &use_socket_);
            if (use_socket_ == 0)
                DBG(RED "!!! socket disabled. !!!\n" NONE);
        }
        if (strstr(buffer, "socket_port") != NULL) {
            sscanf(buffer, "socket_port=%d", &socket_port_);
            DBG(GREEN "socket port: %d \n", socket_port_);
        }
        if (strstr(buffer, "socket_addr") != NULL) {
            sscanf(buffer, "socket_addr=%s", &socket_addr_);
            DBG(GREEN "socket addr: %s \n", socket_addr_);
        }
    }
    fclose(fp);
    return 0;
}
