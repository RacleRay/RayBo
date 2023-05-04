/*************************************************************************
    > File Name: UserInfo.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _USERINFO_H
#define _USERINFO_H

#include "common/macro.h"
#include "proto/user_info_base.pb.h"
#include <string.h>

namespace raybo {

class UserInfo {
public:
    int FromPb(raybo::UserInfoBase& pb_user);
    int ToPb(raybo::UserInfoBase& pb_user);

private:
    GETSETVAR(int, user_id)
    GETSETVAR(int, from)
    GETSETVAR(int, db_flag)

    GETSETVAR(int, reg_time)
    GETSETVAR(int, login_time)
    GETSETVAR(int, last_login_time)
    GETSETVAR(int, fresh_time)
    GETSETVAR(int, logout_time)

    GETSETSTR(256, user_name)  // 256字节字符数组
    GETSETSTR(256, nick_name)
    GETSETSTR(256, password)
};

}  // namespace raybo

#endif
