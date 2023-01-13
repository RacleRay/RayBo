/*************************************************************************
    > File Name: macro.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _MACRO_H
#define _MACRO_H

#include <string.h>

#define MAX_FRIENDS 10240
#define MAX_CONTENTS 1024
#define MAX_BUFFER_SIZE 10240
#define MAX_MESSAGES 10240
#define MAX_LISTEN_PORTS 1000
#define SLEEP_TIME_MICS 5000
#define BASE_ID 10001
#define BASE_MESSAGE_ID 100001

#define GETSETVAR(type, name)                                                  \
private:                                                                       \
    type name##_;                                                              \
                                                                               \
public:                                                                        \
    const type& name() const { return name##_; }                               \
    void        set_##name(const type& value) { name##_ = value; }


#define GETSETSTR(size, name)                                                  \
private:                                                                       \
    char name##_[size];                                                        \
                                                                               \
public:                                                                        \
    const char* name() const { return name##_; }                               \
    void        set_##name(const char* value) { strncpy(name##_, value, size); }


#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

#endif
