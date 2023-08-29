//#define _CRT_SECURE_NO_WARNINGS
//#include <bits/stdc++.h>
//#include "../sqlite_functions/sqlite3.h"
//#include "./database_operations.h"

//using namespace std;

//string db_path = "./database_files/furure_chat.db";


//int main( int argc, char* argv[] ) {
//    ////初始化数据库和SQL语句
//    DataBase db = DataBase( db_path );
//    string sql;

//    //auto i_res = InsertResult();
//    //auto s_res = SelectResult();
//    //string s_sql = "select * from friend_library";
//    //s_res.executeSelect( db, s_sql );

//    //save_downloaded_data_to_database( db, i_res, s_res, "user_login_info" );
//    //sql = "INSERT INTO user_info VALUES (12345, 'JohnDoe', ':/images/user_man.png', 'Avid explorer and learner.');\
//    //    INSERT INTO user_info VALUES( 67890, 'JaneSmith', ':/images/user_woman.png', 'Coffee lover and coding enthusiast.' );\
//    //INSERT INTO user_info VALUES( 98765, 'AliceWonder', ':/images/more.png', 'Curious mind and tech geek.' );\ ";
//    auto i_res = InsertResult();
//    i_res.executeInsert( db, sql );
//    i_res.check_result();

//    sql = "select * from user_info";
//    auto s_res = SelectResult();
//    s_res.executeSelect( db, sql );
//    s_res.check_result();
//    for ( int i = 0; i < s_res.row; i++ ) {
//        for ( int j = 0; j < s_res.column; j++ ) {
//            cout << s_res.data[i][j] << " ";
//        }
//        cout << endl;
//    }
    
//    auto v_s_res = get_all_data_from_table( db, "user_info" );
//    for ( auto& i : v_s_res ) {
//        for ( auto& j : i ) {
//            cout << j << " ";
//        }
//        cout << endl;
//    }
//}

