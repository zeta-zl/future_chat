#include "database_operations.h"
#include <QApplication>
#include <qlogging.h>
#include <qdebug.h>


#if defined(_WIN32) || defined(_MSC_VER) 
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif

# define MAX_BUSY_HANDLE_TIME 5//遇到锁时,重复 MAX_BUSY_HANDLE_TIME 次






void SelectResult::executeSelect( sqlite3* db, string sql ) {
    qDebug()<<sql.c_str();
    char* gb_string = this->U2G( sql.c_str() );
    if ( this->raw_data != nullptr ) {
        sqlite3_free_table( this->raw_data );
    }
    for(int i=0;i<MAX_BUSY_HANDLE_TIME;i++){
        this->error_code = sqlite3_get_table( db,
            gb_string,
            &this->raw_data,
            &(this->row),
            &(this->column),
            &(this->error_mes) );
        if(this->error_code==SQLITE_OK){
            break;
        }
        else {
            __sleep( 10 );
            qDebug()<<i<<this->error_code;
            continue;
        }

    }


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

    if ( gb_string ) delete[] gb_string;
}

bool SelectResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Select successed\n" );
        return true;
    }
    else {
        fprintf( stderr, "Select failed: %s\n", this->error_mes );
        return false;
    }
}


void InsertResult::executeInsert( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void InsertResult::batch_executeInsert( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

bool InsertResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Insert successed\n" );
        return true;
    }
    else {
        fprintf( stderr, "Insert failed: %s\n", this->error_mes );
        return false;
    }
}

void DeleteResult::executeDelete( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void DeleteResult::batch_executeDelete( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

bool DeleteResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Delete successed\n" );
        return true;
    }
    else {
        fprintf( stderr, "Delete failed: %s\n", this->error_mes );
        return false;
    }
}

void UpdateResult::executeUpdate( sqlite3* db, string sql ) {
    this->executeSQL( db, sql );
}

void UpdateResult::batch_executeUpdate( sqlite3* db, vector<string> sql ) {
    this->batch_executeSQL( db, sql );
}

bool UpdateResult::check_result() {
    if ( this->error_code == SQLITE_OK ) {
        fprintf( stdout, "Update successed\n" );
        return true;
    }
    else {
        fprintf( stderr, "Update failed: %s\n", this->error_mes );
        return false;
    }
}

void SQLResult::executeSQL( sqlite3* db, const char* sql ) {
    if ( this->error_mes != nullptr ) {
        sqlite3_free( this->error_mes );
    }
    //printf( "char* sql:%s\n", sql );
    for ( int tryed_times = 0; tryed_times < MAX_BUSY_HANDLE_TIME; tryed_times++ ) {
        this->error_code = sqlite3_exec( db, sql, 0, 0, &(this->error_mes) );

        if ( this->error_code != SQLITE_BUSY ) {
            break;
        }
        else {
            __sleep( 10 );
            continue;
        }
    }
}

void SQLResult::executeSQL( sqlite3* db, string sql ) {
    //cout <<"\nstring: "<< sql << endl;
    char* gb_string = U2G( sql.c_str() );
    this->executeSQL( db, gb_string );
    if ( gb_string ) delete[] gb_string;
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

void save_downloaded_data_to_database( DataBase& db, InsertResult& i_res, SelectResult& s_res, string table_name ) {
    vector<string> sql_list;

    // 使用格式化字符串生成插入 SQL 语句并添加到 sql_list 中
    for ( int i = 0; i < s_res.row; ++i ) {

        stringstream sqlStream;
        sqlStream << "INSERT INTO " << table_name << " VALUES (";
        for ( int j = 0; j < s_res.column; j++ ) {
            if ( j > 0 ) {
                sqlStream << ",";
            }
            sqlStream << "'" << s_res.data[i][j] << "'";
        }
        sqlStream << ")";
        sql_list.push_back( sqlStream.str() );

    }
    i_res.batch_executeInsert( db, sql_list );

}

vector<vector<string>> convert_select_result_to_vector( SelectResult& s_res ) {
    vector<vector<string>> temp( s_res.row, vector<string>( s_res.column ) );
    for ( int i = 0; i < s_res.row; i++ ) {
        for ( int j = 0; j < s_res.column; j++ ) {
            temp[i][j] = s_res.data[i][j];
        }
    }
    return temp;
}


vector<vector<string>> get_all_data_from_table( DataBase db, string table_name ) {
    SelectResult s_res = SelectResult();
    string sql = "select * from " + table_name;
    s_res.executeSelect( db, sql );
    return convert_select_result_to_vector( s_res );
}

