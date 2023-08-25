//#define _CRT_SECURE_NO_WARNINGS
//#include <bits/stdc++.h>  
//#include "../sqlite_functions/sqlite3.h"
//#include "./database_operations.h"
//
//using namespace std;
//
//string db_path = "./database_files/furure_chat.db"; 
//
//
//int main( int argc, char* argv[] ) {
//    //初始化数据库和SQL语句
//    DataBase db = DataBase( db_path );
//    string sql;
//
//    //插入
//    InsertResult i_res = InsertResult();
//    sql = "insert into friend_library values (1,'test1' )";
//    i_res.executeInsert( db, sql );
//    i_res.check_result();
//
//    //批量插入
//    auto sql_ls = vector<string>{ "insert into friend_library values (2,'test2' );",
//        "insert into friend_library values (3,'test3' );",
//        "insert into friend_library values (4,'test4' );" };
//    i_res.batch_executeInsert( db, sql_ls );
//    i_res.check_result();
//
//    //删除
//    DeleteResult d_res = DeleteResult();
//    sql = "delete from friend_library where account=4;";
//    d_res.executeDelete( db, sql );
//    d_res.check_result();
//
//    //更新
//    UpdateResult u_res = UpdateResult();
//    sql = "update friend_library set profile_image_path = 'test_update' where account=1";
//    u_res.executeUpdate( db, sql );
//    u_res.check_result();
//
//    //查询
//    SelectResult q_res = SelectResult();
//    sql = "select * from friend_library";
//    q_res.executeSelect( db, sql );
//    q_res.check_result();
//
//    //输出查询结果
//    for ( int i = 0; i < q_res.row; i++ ) {
//        for ( int j = 0; j < q_res.column; j++ ) {
//            cout << q_res.data[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//
//}
