/*************************************************************************
    > File Name: UserManager.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "Database.h"
#include "UserInfo.h"
#include "common/macro.h"

namespace raybo {

class UserManager {
private:
    UserInfo users_[MAX_BUFFER_SIZE];
    GETSETVAR(int, user_count)
    GETSETVAR(int, idle_id)
private:
    Database* db_svr_;

public:
    int Start(Database* db_svr);
    int Proc();
    int Restart();
    int Shutdown();

public:
    UserInfo* GetUser(int user_id);
    int       CheckExist(int user_id);
    int       CreateUser(const char* user_name, const char* password, int from,
                         int reg_time);
    int       DeleteUser(int user_id);
    int       SaveUser();  // todo
    int       LoginCheck(const char* user_name, const char* password);
    int       UserLogout(int user_id, int time_now);
    int       GetUserIdByUserName(const char* user_name);
    int       UpdateLoginTime(int user_id, int time_now);
    // int UpdateUserLogoutTime(int user_id,int time_now);
    // int UpdateUserFreshTime(int user_id,int time_now);
};

}  // namespace raybo

#endif
