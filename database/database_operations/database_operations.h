#pragma once
#include "../sqlite_functions/sqlite3.h"

class QueryResult {
public:
    int column = 0;//列数
    int row = 0;//行数
    char*** row_data = nullptr;//数据    
    int error_code = SQLITE_OK;//错误代码，初始值为0
    char* error_mes = nullptr;//错误信息

    void executeQuery( sqlite3* db, const char* sql ) {
        char** temp_data = nullptr;
        this->error_code = sqlite3_get_table( db,
            sql,
            &temp_data,
            &(this->row),
            &(this->column),
            &(this->error_mes) );

        if ( this->error_code == SQLITE_OK ) {
            this->row_data = new
                char** [this->row];
            for ( int i = 0; i < this->row; i++ ) {
                this->row_data[i] = new char* [this->column];
            }
            for ( int i = 1; i < this->row; i++ ) {
                for ( int j = 0; j < this->column; j++ ) {
                    this->row_data[i][j] = temp_data[i * this->column + j];
                }
            }
        }
    }

};
void executeQuery( sqlite3* db, const char* sql, QueryResult& result );
