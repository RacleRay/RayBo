/*************************************************************************
    > File Name: BusManager.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _BUSMANAGER_H
#define _BUSMANAGER_H

#include "common/macro.h"
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

class BusBlock {
public:
    BusBlock* next;
    char*     used;
    int*      size;
    char*     data;
};

class Channel {
public:
    char*     name;
    int*      from;
    int*      to;
    BusBlock* block;
};

class BusManager {
private:
    int      shm_id;
    char*    shmp;
    Channel* channel_[4];

public:
    char send_buffer[MAX_BUFFER_SIZE];

public:
    int Init();
    int BusInit();
    int ChannelInit();
    int ChannelTest();
    int ChannelShow();
    int ChannelQuickShow();
    int Detach();
    int Remove();

    char*     MutableChannelName(int i);
    int*      MutableChannelFrom(int i);
    int*      MutableChannelTo(int i);
    int       MutableChannelBlock(int i);
    BusBlock* MutableChannelBlockNext(int i);
    char*     MutableChannelBlockUsed(int i);
    int*      MutableChannelBlockSize(int i);
    char*     MutableChannelBlockData(int i);

    int GetChannelIndex(int from, int to);

    char* GetChannelName(int from, int to);
    int   CheckRecv(int target_id);
    int   RecvSize(int from, int to);
    char* Recv(int from, int to);
    int   ChannelsClear();
    int   Clear(int from, int to);
    int   Send(int from, int to, char* data, int size);
};

#endif
