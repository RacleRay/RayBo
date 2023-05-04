/*************************************************************************
    > File Name: Config.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

#include "common/macro.h"

namespace raybo {
class Config {
    GETSETVAR(int, use_socket)
    GETSETVAR(int, socket_port)
    GETSETSTR(256, socket_addr)
public:
    int ReadConfig(int);
};
}  // namespace raybo


#endif
