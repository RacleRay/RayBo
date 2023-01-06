/*************************************************************************
    > File Name: relationInfo.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _RELATIONINFO_H
#define _RELATIONINFO_H

#include "common/macro.h"
#include <string.h>

namespace raybo {

class RelationInfo {
private:
    GETSETVAR(int, user_id)  // user_ind_属性，user_id()和set_user_id(int) 方法
    GETSETVAR(int, friend_count)
    GETSETVAR(int, black_count)
    int friend_list_[MAX_FRIENDS];
    int black_list_[MAX_FRIENDS];

public:
    int CheckFriend(int other_id);
    int CheckBlack(int other_id);
    int AddFriend(int other_id);
    int AddBlack(int other_id);
    int DeleteFriend(int other_id);
    int DeleteBlack(int other_id);
    int GetFriendByIndex(int index);
    int GetBlackByIndex(int index);
};


}  // namespace raybo


#endif
