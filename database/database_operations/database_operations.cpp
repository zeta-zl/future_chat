#include "database_operations.h"


void executeQuery( sqlite3* db, const char* sql, QueryResult& result ) {
    char** temp_data = nullptr;
    result.error_code =
        sqlite3_get_table( db
            , sql
            , &temp_data
            , &(result.row)
            , &(result.column)
            , &(result.error_mes) );
    if ( result.error_code == SQLITE_OK ) {
        result.row_data = new char** [result.row];
        for ( int i = 0; i < result.row; i++ ) {
            result.row_data[i] = new char* [result.column];
        }
        for ( int i = 1; i < result.row; i++ ) {
            for ( int j = 0; j < result.column; j++ ) {
                result.row_data[i][j] = temp_data[i * result.column + j];
            }
        }
    }

}