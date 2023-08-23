#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>  
#include "../sqlite_functions/sqlite3.h"
#include "./database_operations.h"

using namespace std;
string db_path = "./database_files/furure_chat.db";
//string db_path = "test1.db";
string init_str = "CREATE TABLE message_library ( \
    environment INT NOT NULL,\
    id INT NOT NULL,\
    source INT,\
    type VARCHAR(255),\
    content TEXT,\
    time TIMESTAMP,\
    status INT,\
    PRIMARY KEY (environment, id)\
);\
CREATE TABLE friend_library (\
account INT PRIMARY KEY,\
profile_image_path VARCHAR( 255 )\
);\
CREATE TABLE user_info (\
account INT PRIMARY KEY,\
nickname VARCHAR( 255 ),\
profile_image_path VARCHAR( 255 ),\
signature TEXT\
);\
CREATE TABLE user_login_info (\
account INT PRIMARY KEY,\
password VARCHAR( 255 )\
);\
CREATE TABLE user_other_info (\
account INT PRIMARY KEY,\
gender VARCHAR( 20 ),\
birthday DATE,\
location VARCHAR( 255 ),\
education_experience TEXT\
);\
CREATE TABLE group_chat (\
group_number INT PRIMARY KEY,\
name VARCHAR( 255 ),\
group_image_path VARCHAR( 255 ));";






static int callback( void* NotUsed, int argc, char** argv, char** azColName ) {
    
    int i;
    for ( i = 0; i < argc; i++ ) {
        printf( "%s = %s  ", azColName[i], argv[i] ? argv[i] : "NULL" );
    }
    printf( "\n" );
    return 0;
}

int main( int argc, char* argv[] ) {
    sqlite3* db;
    char* zErrMsg = 0;
    int  rc;
    const char* sql;

    /* Open database */
    rc = sqlite3_open( db_path.c_str(), &db);
    if ( rc ) {
        fprintf( stderr, "Can't open database: %s\n", sqlite3_errmsg( db ) );
        exit( 0 );
    }
    else {
        fprintf( stdout, "Opened database successfully\n" );
    }
    /* Create SQL statement */
    //sql = init_str.c_str();
    sql = "";

    /* Execute SQL statement */
    rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg );
    if ( rc != SQLITE_OK ) {
        fprintf( stderr, "SQL error: %s\n", zErrMsg );
        sqlite3_free( zErrMsg );
    }
    else {
        fprintf( stdout, "Records created successfully\n" );
    }
    sqlite3_close( db );
    return 0;
    //
    //sql = "SELECT * from COMPANY";
    //QueryResult ret = QueryResult();
    ////query_table( db, sql, ret );
    //ret.executeQuery( db, sql );
    //for ( int i = 1; i < ret.row; i++ ) {
    //    for ( int j = 0; j < ret.column; j++ ) {
    //        cout << ret.row_data[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    //sqlite3_close( db );
    return 0;
}




