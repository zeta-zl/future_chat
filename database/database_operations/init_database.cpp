#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>  
#include "../sqlite_functions/sqlite3.h"
#include "./database_operations.h"

using namespace std;
namespace {
    string db_path = "./database_files/furure_chat.db";
    string init_sql = "CREATE TABLE IF NOT EXISTS message_library ( \
    environment INT NOT NULL,\
    id INT NOT NULL,\
    source INT,\
    type VARCHAR(255),\
    content TEXT,\
    time TIMESTAMP,\
    status INT,\
    PRIMARY KEY (environment, id)\
);\
CREATE TABLE IF NOT EXISTS friend_library (\
account INT PRIMARY KEY,\
profile_image_path VARCHAR( 255 )\
);\
CREATE TABLE IF NOT EXISTS user_info (\
account INT PRIMARY KEY,\
nickname VARCHAR( 255 ),\
profile_image_path VARCHAR( 255 ),\
signature TEXT\
);\
CREATE TABLE IF NOT EXISTS user_login_info (\
account INT PRIMARY KEY,\
password VARCHAR( 255 )\
);\
CREATE TABLE IF NOT EXISTS user_other_info (\
account INT PRIMARY KEY,\
gender VARCHAR( 20 ),\
birthday DATE,\
location VARCHAR( 255 ),\
education_experience TEXT\
);\
CREATE TABLE IF NOT EXISTS group_chat (\
group_number INT PRIMARY KEY,\
name VARCHAR( 255 ),\
group_image_path VARCHAR( 255 ));";
    void init_database( DataBase& db ) {
        char* error_mes = nullptr;
        int error_code = sqlite3_exec( db, init_sql.c_str(), 0, 0, 0 );
        if ( error_code == SQLITE_OK ) {
            fprintf( stdout, "Init successed\n" );
        }
        else {
            fprintf( stderr, "Init failed: %s\n",error_mes );
        }

    }
}




int main( int argc, char* argv[] ) {
    DataBase db( db_path );
    init_database( db );
    return 0;
}




