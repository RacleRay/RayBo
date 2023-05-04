/*************************************************************************
    > File Name: Database.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "Database.h"
#include "common/return_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int raybo::Database::Init() {
    FILE* fp = fopen("mysql.ini", "r");
    if (fp == NULL) {
        perror("File mysql.ini not exists.");
        return DB_CONN_INIT_FAIL;
    }
    fscanf(fp, "%s", mysql_username);
    fscanf(fp, "%s", mysql_password);
    fclose(fp);

    conn = mysql_init(NULL);
    if (conn == NULL) {
        return DB_CONN_INIT_FAIL;
    }
    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username, mysql_password,
                              "raybo", 0, NULL, 0);
    if (conn == NULL) {
        return DB_CONN_CONNECT_FAIL;
    }
    return SUCCESS;
}


int raybo::Database::execSql(std::string sql) {
    if (mysql_query(conn, sql.c_str())) {
        return DB_QUERY_FAIL;
    }
    else {
        result = mysql_use_result(conn);
        if (result) {
            int n_row   = mysql_num_rows(result);
            int n_field = mysql_num_fields(result);
            DBG(BLUE "rows: %d, fields: %d\n" NONE, n_row, n_field);

            while (result) {
                // 在事务中一条条查询，不用mysql_store_result()因为一次占用太多内存
                row = mysql_fetch_row(result);
                if (row == NULL) {
                    DBG(YELLOW "No more row\n" NONE);
                    break;
                }
                for (int i = 0; i < n_field; ++i) {
                    DBG("%s\t", row[i]);
                }
                DBG("\n");
            }

            mysql_free_result(result);
        }
    }

    return SUCCESS;
}


int raybo::Database::InsertUser(UserInfo& user) {
    raybo::UserInfoBase pb_user;
    user.ToPb(pb_user);  // protobuf 格式

    DBG(BLUE "user    password: %s\n" NONE, user.password());
    DBG(BLUE "pb_user password: %s\n" NONE, pb_user.password().c_str());

    char user_id[256];
    sprintf(user_id, "%d", user.user_id());

    char user_info[MAX_BUFFER_SIZE];
    pb_user.SerializeToArray(user_info, MAX_BUFFER_SIZE);

    // user_info中有 0 ，字符串会被截断
    // 所以，统一加上 'a'，分别在每个字节的高4位和低4位进行
    char user_info_encr[MAX_BUFFER_SIZE];
    for (int i = 0; i < pb_user.ByteSize(); i++) {
        int l                 = user_info[i] & 0x000f;
        int h                 = (user_info[i] & 0x00f0) >> 4;
        user_info_encr[i * 2]     = h + 'a';
        user_info_encr[i * 2 + 1] = l + 'a';
    }

    std::string insertSql = "insert into ra_users values ('";
    insertSql += user_id;
    insertSql += "','";
    insertSql += user_info_encr;
    insertSql += "')";
    DBG(GREEN "insert: %s\n" NONE, insertSql.c_str());

    int ret = mysql_query(conn, insertSql.c_str());
    if (ret == 0) {
        return SUCCESS;
    }
    else {
        DBG(RED "insert user failed : %d\n" NONE, ret);
        return DB_QUERY_FAIL;
    }
    return SUCCESS;
}


// 获取所有用户，配合 GetUsersOneByOne, GetUsersEnd 使用
int raybo::Database::GetUsersBegin() {
    if (transection() == 1) return DB_BUSY;  // 事务锁定中

    set_transection(1);
    int ret = mysql_query(conn, "select * from ra_users;");
    if (ret) {
        set_transection(0);
        return DB_QUERY_FAIL;
    }

    result = mysql_use_result(conn);
    return SUCCESS;
}


int raybo::Database::GetUsersOneByOne(UserInfo& user) {
    if (result) {
        row = mysql_fetch_row(result);
        if (row == NULL)
            return DB_NO_MORE_DATA;

        raybo::UserInfoBase pb_user;
        // row[0]:user_id  row[1]:user_info, protobuf
        int info_len = strlen(row[1]);
        char user_info_decr[MAX_BUFFER_SIZE];

        // InsertUser 中处理 \0 字符的反向恢复操作
        for (int i = 0; i < info_len / 2; ++i) {
            user_info_decr[i] = (row[1][2 * i] - 'a') << 4 + \
                                (row[1][2 * i + 1] - 'a');
        }

        int ret = pb_user.ParseFromArray(user_info_decr, MAX_BUFFER_SIZE);
        user.FromPb(pb_user);
    } else {
        return DB_NO_MORE_DATA;
    }

    return SUCCESS;
}


int raybo::Database::GetUsersEnd() {
    mysql_free_result(result);
    set_transection(0);
    return SUCCESS;
}
