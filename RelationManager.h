/*************************************************************************
    > File Name: RelationManager.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _RELATIONMANAGER_H
#define _RELATIONMANAGER_H

#include "RelationInfo.h"

namespace raybo {
class RelationManager {
private:
    RelationInfo relations_[MAX_FRIENDS];
    GETSETVAR(int, relation_count)

public:
    int Start();
    int Proc();
    int Restart();
    int Shutdown();

    int           UserRelationInit(int user_id);
    RelationInfo* GetRelation(int user_id);
    int           AddFriend(int user_id, int other_id);
    int           DelFriend(int user_id, int other_id);
};
}  // namespace raybo


#endif
