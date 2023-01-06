/*************************************************************************
    > File Name: MessageInfo.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _MESSAGEINFO_H
#define _MESSAGEINFO_H

#include "common/macro.h"
#include <string.h>

namespace raybo {
class MessageInfo {
    GETSETVAR(int, user_id)
    GETSETVAR(int, message_id)
    GETSETVAR(int, publish_time)
    GETSETSTR(MAX_CONTENTS, content)
};
}  // namespace raybo

#endif
