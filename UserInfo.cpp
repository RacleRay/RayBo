/*************************************************************************
    > File Name: UserInfo.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "UserInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int raybo::UserInfo::FromPb(raybo::UserInfoBase& pb_user) {
    set_user_id(pb_user.user_id());
    set_user_name(pb_user.user_name().c_str());
    set_password(pb_user.password().c_str());
    set_from(pb_user.from());
    set_login_time(pb_user.login_time());
    set_last_login_time(pb_user.last_login_time());
    set_fresh_time(pb_user.fresh_time());
    return 0;
}

int raybo::UserInfo::ToPb(raybo::UserInfoBase& pb_user) {
    pb_user.set_user_id(user_id());
    pb_user.set_user_name(user_name());
    pb_user.set_password(password());
    pb_user.set_from(from());
    pb_user.set_login_time(login_time());
    pb_user.set_last_login_time(last_login_time());
    pb_user.set_fresh_time(fresh_time());
    return 0;
}
