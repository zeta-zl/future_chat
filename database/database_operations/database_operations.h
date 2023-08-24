#pragma once
#include "../sqlite_functions/sqlite3.h"
#include<bits/stdc++.h>
#include <codecvt>
#include <string>
using namespace std;


class SQLResult {
private:
    void batch_executeSQL( sqlite3* db, vector<const char*> sql );
protected:
    //UTF-8到GB2312的转换
    char* U2G( const char* utf8 );
    //GB2312到UTF-8的转换
    char* G2U( const char* gb2312 );
    void executeSQL( sqlite3* db, const char* sql );
public:
    int error_code = SQLITE_OK; // 错误代码，初始值为0
    char* error_mes = nullptr; // 错误信息

    SQLResult() {}
    virtual ~SQLResult() {
        if ( error_mes != nullptr ) {
            sqlite3_free( error_mes );
        }
    }

    virtual void check_result() = 0;

    void executeSQL( sqlite3* db, string sql );
    void batch_executeSQL( sqlite3* db, vector<string> sql );
};

class InsertResult : private SQLResult {
private:
public:
    void executeInsert( sqlite3* db, string sql );
    void batch_executeInsert( sqlite3* db, vector<string> sql );
    void check_result();
};

class DeleteResult : private SQLResult {
private:
public:
    void executeDelete( sqlite3* db, string sql );
    void batch_executeDelete( sqlite3* db, vector<string> sql );
    void check_result();
};

class UpdateResult : private SQLResult {
private:
public:
    void executeUpdate( sqlite3* db, string sql );
    void batch_executeUpdate( sqlite3* db, vector<string> sql );
    void check_result();
};

class SelectResult : public SQLResult {
private:
public:
    int column = 0;//列数
    int row = 0;//行数
    char*** data = nullptr;//数据    
    char** raw_data = nullptr;//原始数据
    virtual ~SelectResult() {
        sqlite3_free_table( this->raw_data );
        for ( int i = 0; i < this->row; i++ ) {
            delete[] this->data[i];
        }
        delete[] this->data;
    }

    void executeSelect( sqlite3* db, string sql );
    void check_result();
};


class DataBase {
private:
    sqlite3* db;
    int is_valid = 0;
    void initialize( const char* path );
public:
    ~DataBase();
    DataBase( string path ) {
        initialize( path.c_str() );
    }
    DataBase( char* path ) {
        initialize( path );
    }
    operator sqlite3* () {
        return this->db;
    }
};

void __sleep(int a);