#include "database_operations.h"

#include <atlstr.h>

#if defined(_WIN32) || defined(_MSC_VER) 
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif

# define MAX_BUSY_HANDLE_TIME 5//遇到锁时,重复 MAX_BUSY_HANDLE_TIME 次






void SelectResult::executeSelect( sqlite3* db, string sql ) {
    char* gb_string = this->U2G( sql.c_str() );
    if ( this->raw_data != nullptr ) {
        sqlite3_free_table( this->raw_data );
    }
    this->error_code = sqlite3_get_table( db,
        gb_string,
        &this->raw_data,
        &(this->row),
        &(this->column),
        &(this->error_mes) );

    if ( this->error_code == SQLITE_OK ) {
        this->data = new
            char** [this->row];
        for ( int i = 0; i < this->row; i++ ) {
            this->data[i] = new char* [this->column];
        }
        for ( int i = 0; i < this->row; i++ ) {
            for ( int j = 0; j < this->column; j++ ) {
                this->data[i][j] = this->raw_data[(i + 1) * this->column + j];
            }
        }
    }
}

void SelectResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Select successed\n" );
    }
    else {
        fprintf( stderr, "Select failed: %s\n", this->error_mes );
    }
}


void InsertResult::executeInsert( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void InsertResult::batch_executeInsert( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

void InsertResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Insert successed\n" );
    }
    else {
        fprintf( stderr, "Insert failed: %s\n", this->error_mes );
    }
}

void DeleteResult::executeDelete( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void DeleteResult::batch_executeDelete( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

void DeleteResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Delete successed\n" );
    }
    else {
        fprintf( stderr, "Delete failed: %s\n", this->error_mes );
    }
}

void UpdateResult::executeUpdate( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void UpdateResult::batch_executeUpdate( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

void UpdateResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Update successed\n" );
    }
    else {
        fprintf( stderr, "Update failed: %s\n", this->error_mes );
    }
}

void SQLResult::executeSQL( sqlite3* db, const char* sql ) {
    if ( this->error_mes != nullptr ) {
        sqlite3_free( this->error_mes );
    }
    for ( int tryed_times = 0; tryed_times < MAX_BUSY_HANDLE_TIME; tryed_times++ ) {
        this->error_code = sqlite3_exec( db, sql, 0, 0, &(this->error_mes) );

        if ( this->error_code != SQLITE_BUSY ) {
            break;
        }
        else {
            Sleep( 10 );
            continue;
        }
    }
}

void SQLResult::executeSQL( sqlite3* db, string sql ) {
    char* gb_string = U2G( sql.c_str() );
    this->executeSQL( db, gb_string );
}

//用于批量执行SQL语句
void SQLResult::batch_executeSQL( sqlite3* db, vector<const char*> sql ) {
    sqlite3_exec( db, "begin;", 0, 0, 0 );
    for ( auto &i : sql ) {
        if ( this->error_code == SQLITE_OK ) {
            this->executeSQL( db, i );            
        }
        else {
            break;
        }
    }
    if ( this->error_code == SQLITE_OK ) {
        sqlite3_exec( db, "commit;", 0, 0, 0 );
    }
    else {
        sqlite3_exec( db, "rollback;", 0, 0, 0 );
    }
}

char* SQLResult::U2G( const char* utf8 ) {
    int len = MultiByteToWideChar( CP_UTF8, 0, utf8, -1, NULL, 0 );
    wchar_t* wstr = new wchar_t[len + 1];
    memset( wstr, 0, len + 1 );
    MultiByteToWideChar( CP_UTF8, 0, utf8, -1, wstr, len );
    len = WideCharToMultiByte( CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL );
    char* str = new char[len + 1];
    memset( str, 0, len + 1 );
    WideCharToMultiByte( CP_ACP, 0, wstr, -1, str, len, NULL, NULL );
    if ( wstr ) delete[] wstr;
    return str;
}

char* SQLResult::G2U( const char* gb2312 ) {
    int len = MultiByteToWideChar( CP_ACP, 0, gb2312, -1, NULL, 0 );
    wchar_t* wstr = new wchar_t[len + 1];
    memset( wstr, 0, len + 1 );
    MultiByteToWideChar( CP_ACP, 0, gb2312, -1, wstr, len );
    len = WideCharToMultiByte( CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL );
    char* str = new char[len + 1];
    memset( str, 0, len + 1 );
    WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, len, NULL, NULL );
    if ( wstr ) delete[] wstr;
    return str;
}



void SQLResult::batch_executeSQL( sqlite3* db, vector<string> sql ) {
    sqlite3_exec( db, "begin;", 0, 0, 0 );
    for ( auto& i : sql ) {
        if ( this->error_code == SQLITE_OK ) {
            this->executeSQL( db, i );
        }
        else {
            break;
        }
    }
    if ( this->error_code == SQLITE_OK ) {
        sqlite3_exec( db, "commit;", 0, 0, 0 );
    }
    else {
        sqlite3_exec( db, "rollback;", 0, 0, 0 );
    }
}

void DataBase::initialize( const char* path ) {
    int rc = sqlite3_open( path, &db );
    if ( rc ) {
        fprintf( stderr, "Can't open database: %s\n", sqlite3_errmsg( db ) );
        exit( 0 );
    }
    else {
        fprintf( stdout, "Opened database successfully\n" );
        is_valid = 1;
    }
}

DataBase::~DataBase() {
    sqlite3_close( this->db );
}
