/*************************************************************************
    > File Name: Database.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _DATABASE_H
#define _DATABASE_H

#include "UserInfo.h"
#include "mysql/mysql.h"
#include <iostream>
#include <string>

namespace raybo {
class Database {
private:
    GETSETVAR(int, transection)
    int mysql_defined;

    MYSQL*     conn;
    MYSQL_RES* result;
    MYSQL_ROW  row;

    char mysql_username[256];
    char mysql_password[256];

public:
    int Init();
    int execSql(std::string sql);
    int GetUsersBegin();
    int GetUsersOneByOne(UserInfo& user);
    int GetUsersEnd();
    int InsertUser(UserInfo& user);
};
}  // namespace raybo

#endif
