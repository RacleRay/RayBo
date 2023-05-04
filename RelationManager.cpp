/*************************************************************************
    > File Name: RelationManager.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "RelationManager.h"
#include "common/return_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int raybo::RelationManager::Start() {}
int raybo::RelationManager::Proc() {}
int raybo::RelationManager::Shutdown() {}
int raybo::RelationManager::Restart() {}

int raybo::RelationManager::UserRelationInit(int user_id) {
    for (int i = 0; i < relation_count_; i++) {
        if (relations_[i].user_id() == user_id) {
            return RELATION_EXIST;
        }
    }
    if (relation_count_ < 10239) {
        relations_[relation_count_].set_user_id(user_id);
        relation_count_++;
        return SUCCESS;
    }
    else {
        return RELATION_TO_MUCH;
    }
}

raybo::RelationInfo* raybo::RelationManager::GetRelation(int user_id) {
    for (int i = 0; i < relation_count_; i++) {
        if (relations_[i].user_id() == user_id) {
            return &relations_[i];
        }
    }
    return NULL;
}

int raybo::RelationManager::AddFriend(int user_id, int other_id) {
    RelationInfo* relation = GetRelation(user_id);
    if (relation == NULL) {
        return RELATION_NOT_EXIST;
    }
    int ret = relation->AddFriend(other_id);
    return ret;
}

int raybo::RelationManager::DelFriend(int user_id, int other_id) {
    RelationInfo* relation = GetRelation(user_id);
    if (relation == NULL) {
        return RELATION_NOT_EXIST;
    }
    int ret = relation->DeleteFriend(other_id);
    return ret;
}
