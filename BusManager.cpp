/*************************************************************************
    > File Name: BusManager.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "BusManager.h"

#define SIZE_BUS_FLAG 16
#define SIZE_CHANNEL sizeof(Channel)
#define SIZE_CHANNEL_NAME 256
#define SIZE_CHANNEL_FROM sizeof(int)
#define SIZE_CHANNEL_TO sizeof(int)
#define SIZE_BLOCK sizeof(BusBlock)
#define SIZE_BLOCK_NEXT sizeof(BusBlock*)
#define SIZE_BLOCK_USED 8
#define SIZE_BLOCK_SIZE sizeof(int)
#define SIZE_BLOCK_DATA 10240

#define OFFSET_BUS_FLAG 0
#define OFFSET_CHANNEL 0
#define OFFSET_CHANNEL_NAME (OFFSET_CHANNEL + SIZE_CHANNEL)
#define OFFSET_CHANNEL_FROM (OFFSET_CHANNEL_NAME + SIZE_CHANNEL_NAME)
#define OFFSET_CHANNEL_TO (OFFSET_CHANNEL_FROM + SIZE_CHANNEL_FROM)
#define OFFSET_CHANNEL_BLOCK (OFFSET_CHANNEL_TO + SIZE_CHANNEL_TO)
#define OFFSET_CHANNEL_BLOCK_NEXT (OFFSET_CHANNEL_BLOCK + SIZE_BLOCK)
#define OFFSET_CHANNEL_BLOCK_USED (OFFSET_CHANNEL_BLOCK_NEXT + SIZE_BLOCK_NEXT)
#define OFFSET_CHANNEL_BLOCK_SIZE (OFFSET_CHANNEL_BLOCK_USED + SIZE_BLOCK_USED)
#define OFFSET_CHANNEL_BLOCK_DATA (OFFSET_CHANNEL_BLOCK_SIZE + SIZE_BLOCK_SIZE)

#define UNIT_SIZE (OFFSET_CHANNEL_BLOCK_DATA + SIZE_BLOCK_DATA)


int BusManager::Init() {
    DBG("----  Init Shm  ----\n");

    shm_id = shmget((key_t)8998, 102400, IPC_CREAT | 0666);
    if (shm_id < 0) {
        DBG("shmget failed : %d\n", shm_id);
        return 0;
    }
    DBG("shm_id = %d\n", shm_id);

    shmp = (char*)shmat(shm_id, NULL, 0);
    if (*shmp < 0) {
        DBG("shmat failed: %d\n", *shmp);
        return 0;
    }
    DBG("shmp_addr = %p\n", shmp);

    if (*shmp == 0) {
        *shmp = 'Y';  // 首次初始化
        BusInit();
        ChannelInit();
        DBG("----  After All, RUN This ----\n");
        DBG("ipcrm -m %d\n", shm_id);
    }
    else {
        DBG("---- Bus Build Already ----");
    }
    DBG("----  Init Finish!  ----\n");

    return 0;
}

int BusManager::BusInit() {
    DBG("----  Init Bus  ----\n");
    char* cur_addr = shmp + SIZE_BUS_FLAG;

    /* ---- channel0 ~ channel3 ----*/
    for (int i = 0; i < 4; i++) {
        // channel 内存布局
        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i] = (Channel*)cur_addr;
        cur_addr += SIZE_CHANNEL;
        if (DEBUG) DBG("channel_[%d]:%p\n", i, channel_[i]);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->name = cur_addr;
        cur_addr += SIZE_CHANNEL_NAME;
        if (DEBUG) DBG("channel_[%d]->name:%p\n", i, channel_[i]->name);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->from = (int*)cur_addr;
        cur_addr += SIZE_CHANNEL_FROM;
        if (DEBUG) DBG("channel_[%d]->from:%p\n", i, channel_[i]->from);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->to = (int*)cur_addr;
        cur_addr += SIZE_CHANNEL_TO;
        if (DEBUG) DBG("channel_[%d]->to:%p\n", i, channel_[i]->to);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->block = (BusBlock*)cur_addr;
        cur_addr += SIZE_BLOCK;
        if (DEBUG) DBG("channel_[%d]->block:%p\n", i, channel_[i]->block);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->block->next = (BusBlock*)cur_addr;
        cur_addr += SIZE_BLOCK_NEXT;
        if (DEBUG)
            DBG("channel_[%d]->block->next:%p\n", i, channel_[i]->block->next);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->block->used = cur_addr;
        cur_addr += SIZE_BLOCK_USED;
        if (DEBUG)
            DBG("channel_[%d]->block->used:%p\n", i, channel_[i]->block->used);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->block->size = (int*)cur_addr;
        cur_addr += SIZE_BLOCK_SIZE;
        if (DEBUG)
            DBG("channel_[%d]->block->size:%p\n", i, channel_[i]->block->size);

        if (DEBUG) DBG("cur_addr:%p\n", cur_addr);
        channel_[i]->block->data = cur_addr;
        cur_addr += SIZE_BLOCK_DATA;
        if (DEBUG)
            DBG("channel_[%d]->block->data:%p\n", i, channel_[i]->block->data);
    }
    return 0;
}


int BusManager::ChannelInit() {
    DBG("----  Channel Init ----\n");

    for (int i = 0; i < 4; i++) {
        memset(MutableChannelName(i), 0, SIZE_CHANNEL_NAME);
        *MutableChannelBlockUsed(i) = 'N';
        *MutableChannelBlockSize(i) = 0;
        memset(MutableChannelBlockData(i), 0, SIZE_BLOCK_DATA);
    }
    strncpy(MutableChannelName(0), "Usr1->Server", 12);
    *MutableChannelFrom(0) = 11;
    *MutableChannelTo(0)   = 1;

    strncpy(MutableChannelName(1), "Usr2->Server", 12);
    *MutableChannelFrom(1) = 12;
    *MutableChannelTo(1)   = 1;

    strncpy(MutableChannelName(2), "Server->Usr1", 12);
    *MutableChannelFrom(2) = 1;
    *MutableChannelTo(2)   = 11;

    strncpy(MutableChannelName(3), "Server->Usr2", 12);
    *MutableChannelFrom(3) = 1;
    *MutableChannelTo(3)   = 12;

    ChannelShow();
    return 0;
}

int BusManager::ChannelShow() {
    DBG("----  Channel Display  ----\n");
    for (int i = 0; i < 4; i++) {
        DBG("Channel[%d] Name: %s\n", i, MutableChannelName(i));
        DBG("Channel[%d] From: %d\n", i, *MutableChannelFrom(i));
        DBG("Channel[%d] To  : %d\n", i, *MutableChannelTo(i));
        DBG("Channel[%d] Used: %c\n", i, *MutableChannelBlockUsed(i));
        DBG("Channel[%d] Size: %d\n", i, *MutableChannelBlockSize(i));
        DBG("Channel[%d] Data: %s\n", i, MutableChannelBlockData(i));
    }
    return 0;
}

int BusManager::ChannelQuickShow() {
    DBG("----  Channel Quick Show  ----\n");
    for (int i = 0; i < 4; i++) {
        DBG("Channel[%d] Name: %s ", i, MutableChannelName(i));
        DBG("Used: %c ", *MutableChannelBlockUsed(i));
        DBG("Size: %d\n", *MutableChannelBlockSize(i));
    }
    return 0;
}

// 定位到channel name内存
char* BusManager::MutableChannelName(int i) {
    int offset_in  = OFFSET_CHANNEL_NAME;
    int offset_out = i * UNIT_SIZE;
    return (shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel from内存
int* BusManager::MutableChannelFrom(int i) {
    int offset_in  = OFFSET_CHANNEL_FROM;
    int offset_out = i * UNIT_SIZE;
    return (int*)(shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel to内存
int* BusManager::MutableChannelTo(int i) {
    int offset_in  = OFFSET_CHANNEL_TO;
    int offset_out = i * UNIT_SIZE;
    return (int*)(shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel 中 block 内存
int BusManager::MutableChannelBlock(int i) {
    int offset_in  = OFFSET_CHANNEL_BLOCK;
    int offset_out = i * UNIT_SIZE;
    return *((int*)shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel 中 block 的 next 内存
BusBlock* BusManager::MutableChannelBlockNext(int i) {
    int offset_in  = OFFSET_CHANNEL_BLOCK_NEXT;
    int offset_out = i * UNIT_SIZE;
    return (BusBlock*)(shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel 中 block 的 used 内存
char* BusManager::MutableChannelBlockUsed(int i) {
    int offset_in  = OFFSET_CHANNEL_BLOCK_USED;
    int offset_out = i * UNIT_SIZE;
    return (char*)(shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel 中 block 的 size 内存
int* BusManager::MutableChannelBlockSize(int i) {
    int offset_in  = OFFSET_CHANNEL_BLOCK_SIZE;
    int offset_out = i * UNIT_SIZE;
    return (int*)(shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 定位到channel 中 block 的 data 内存
char* BusManager::MutableChannelBlockData(int i) {
    int offset_in  = OFFSET_CHANNEL_BLOCK_DATA;
    int offset_out = i * UNIT_SIZE;
    return (shmp + offset_in + offset_out + SIZE_BUS_FLAG);
}

// 查询 channel index
int BusManager::GetChannelIndex(int from, int to) {
    for (int i = 0; i < 4; i++) {
        if (*MutableChannelTo(i) == to) {
            if (*MutableChannelFrom(i) == from) {
                return i;
            }
        }
    }
    return -1;
}

// 根据channel index查询channel name
char* BusManager::GetChannelName(int from, int to) {
    int idx = GetChannelIndex(from, to);
    if (idx != -1) {
        return MutableChannelName(idx);
    }
    return NULL;
}

// 从channel中接收数据，返回block data地址
char* BusManager::Recv(int from, int to) {
    int idx = GetChannelIndex(from, to);
    if (idx != -1) {
        if (*MutableChannelBlockUsed(idx) == 'Y') {
            *MutableChannelBlockUsed(idx) = 'N';
            return MutableChannelBlockData(idx);
        }
    }
    return NULL;
}

int BusManager::CheckRecv(int target_id) {
    for (int i = 0; i < 4; i++) {
        if (*MutableChannelTo(i) == target_id) {
            if (*MutableChannelBlockUsed(i) == 'Y') {
                DBG("--- [debug] channel %s recv %d bytes.\n",
                    MutableChannelName(i), *MutableChannelBlockSize(i));
                return *MutableChannelFrom(i);
            }
        }
    }
    return -1;
}

int BusManager::RecvSize(int from, int to) {
    int idx = GetChannelIndex(from, to);
    if (idx != -1) {
        return *MutableChannelBlockSize(idx);
    }
    return 0;
}

int BusManager::ChannelsClear() {
    for (int i = 0; i < 4; i++) {
        int size                    = *MutableChannelBlockSize(i);
        *MutableChannelBlockUsed(i) = 'N';
        *MutableChannelBlockSize(i) = 0;
        memset(MutableChannelBlockData(i), 0, size);
    }
    return 0;
}

int BusManager::Clear(int from, int to) {
    int idx = GetChannelIndex(from, to);
    if (idx != -1) {
        int size                      = *MutableChannelBlockSize(idx);
        *MutableChannelBlockUsed(idx) = 'N';
        *MutableChannelBlockSize(idx) = 0;
        memset(MutableChannelBlockData(idx), 0, size);
    }
    return 0;
}

// 向指定channel发送数据，用于不同server进程间的通信
int BusManager::Send(int from, int to, char* data, int size) {
    int idx = GetChannelIndex(from, to);
    if (idx == -1) {
        DBG("----\033[31m[erro] Channel(%d,%d) Not Exist\033[0m\n", from, to);
        return -2;
    }
    char* p_ch_used = MutableChannelBlockUsed(idx);
    int*  p_ch_size = MutableChannelBlockSize(idx);

    if (*p_ch_used != 'N') {
        DBG("----[warn] Channel(%s) Is Busy\n", MutableChannelName(idx));
        return -3;
    }
    if (idx != -1 && *p_ch_used == 'N') {
        strncpy(MutableChannelBlockData(idx), data, size);
        *p_ch_size = size;
        *p_ch_used = 'Y';
        return 0;
    }
    return -1;
}

// 共享内存释放
int BusManager::Detach() {
    int ret = shmdt(shmp);
    if (ret == 0) {
        DBG("----[info]shmdt ok\n");
    }
    else {
        DBG("----[erro]shmdt failed: %d\n", ret);
    }
    return 0;
}

// 共享内存删除
int BusManager::Remove() {
    int ret = shmctl(shm_id, IPC_RMID, 0);
    if (ret == 0) {
        DBG("----[info]shmctl ok\n");
    }
    else {
        DBG("----[erro]shmctl failed: %d\n", ret);
    }
    return 0;
}
