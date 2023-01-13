/*************************************************************************
    > File Name: MessageManager.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H

#include "MessageInfo.h"
#include "common/macro.h"
#include <map>
#include <vector>

namespace raybo {
class MessageManager {
private:
    MessageInfo                     messages_[MAX_MESSAGES];
    std::map<int, std::vector<int>> user_messages_;

    GETSETVAR(int, message_count)
    GETSETVAR(int, cur_message_id)

public:
    MessageInfo*     GetMessage(int user_id, int message_id);
    MessageInfo*     GetMessage(int message_id);
    int              PublishMessage(MessageInfo message);
    int              DeleteMessage(int message_id);
    int              PushUserMessageId(int user_id, int message_id);
    std::vector<int> GetMessageIds(int user_id);

    void Start();
    void Proc();
    void Shutdown();
    void Restart();
};
}  // namespace raybo

#endif
