/*************************************************************************
    > File Name: MessageManager.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "MessageManager.h"
#include "common/return_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void raybo::MessageManager::Start() {
    set_cur_message_id(
        BASE_MESSAGE_ID);  // set first message id that in message storation.
}
void raybo::MessageManager::Proc() {}
void raybo::MessageManager::Shutdown() {}
void raybo::MessageManager::Restart() {}


raybo::MessageInfo* raybo::MessageManager::GetMessage(int user_id,
                                                      int message_id) {
    for (int i = 0; i < message_count_; i++) {
        if (messages_[i].user_id() == user_id
            && messages_[i].message_id() == message_id) {
            return &messages_[i];
        }
    }
    return NULL;
}


raybo::MessageInfo* raybo::MessageManager::GetMessage(int message_id) {
    for (int i = 0; i < message_count_; i++) {
        if (messages_[i].message_id() == message_id) {
            return &messages_[i];
        }
    }
    return NULL;
}


int raybo::MessageManager::PublishMessage(MessageInfo message) {
    if (message_count_ == MAX_MESSAGES - 1) {
        return MESSAGE_TOO_MUCH;
    }
    int avalibe_id = cur_message_id();
    messages_[message_count_].set_message_id(avalibe_id);
    messages_[message_count_].set_user_id(message.user_id());
    messages_[message_count_].set_publish_time(message.publish_time());
    messages_[message_count_].set_content(message.content());

    // 下一个可用index
    ++cur_message_id_;
    ++message_count_;

    return avalibe_id;
}


int raybo::MessageManager::DeleteMessage(int message_id) {
    for (int i = 0; i < message_count_; i++) {
        // 末尾元素覆盖被删除元素
        if (messages_[i].message_id() == message_id) {
            messages_[i].set_message_id(
                messages_[message_count_ - 1].message_id());
            messages_[i].set_user_id(messages_[message_count_ - 1].user_id());
            messages_[i].set_publish_time(
                messages_[message_count_ - 1].publish_time());
            messages_[i].set_content(messages_[message_count_ - 1].content());
            --message_count_;
            return SUCCESS;
        }
        return MESSAGE_NOT_EXIST;
    }
}


std::vector<int> raybo::MessageManager::GetMessageIds(int user_id) {
    auto iter = user_messages_.find(user_id);
    if (iter != user_messages_.end()) {
        return iter->second;
    }
    return std::vector<int>();
}


int raybo::MessageManager::PushUserMessageId(int user_id, int message_id) {
    auto iter = user_messages_.find(user_id);
    if (iter == user_messages_.end()) {  // new user
        std::vector<int> message_ids;
        message_ids.push_back(message_id);
        user_messages_.insert(std::pair<int, std::vector<int>>(user_id, message_ids));
        return PUSH_NEW_USER_MESSAGE_SUCCESS;
    }
    iter->second.push_back(message_id);  // message of existed user
    return PUSH_MESSAGE_SUCCESS;
}