/*************************************************************************
    > File Name: PhotoManager.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "PhotoManager.h"
#include "common/return_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void raybo::PhotoManager::Start() {}
void raybo::PhotoManager::Proc() {}
void raybo::PhotoManager::Shutdown() {}
void raybo::PhotoManager::Restart() {}

int raybo::PhotoManager::CreatePhoto(int user_id) {
    for (int i = 0; i < photo_count_; i++) {
        if (photos_[i].user_id() == user_id) {
            return PHOTO_EXIST;
        }
    }
    if (photo_count_ == 10239) {
        return PHOTO_TOO_MUCH;
    }
    photos_[photo_count_].set_user_id(user_id);
    photos_[photo_count_].set_last_publisher_id(0);
    photo_count_++;
    return SUCCESS;
}

raybo::PhotoInfo* raybo::PhotoManager::GetPhoto(int user_id) {
    for (int i = 0; i < photo_count_; i++) {
        if (photos_[i].user_id() == user_id) {
            return &photos_[i];
        }
    }
    return NULL;
}

int raybo::PhotoManager::UpdatePhoto(int user_id, int publisher_id, int publish_time,
                              int publish_message_id) {
    PhotoInfo* photo = GetPhoto(user_id);
    if (photo == NULL) {
        DBG(RED "photo is null\n" NONE);
        return PHOTO_NOT_EXIST;
    }
    DBG(GREEN "update %d publisher %d\n" NONE, user_id, publisher_id);
    photo->set_last_publisher_id(publisher_id);
    return SUCCESS;
}
