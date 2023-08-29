//#define _CRT_SECURE_NO_WARNINGS
//#include <bits/stdc++.h>
//#include "../sqlite_functions/sqlite3.h"
//#include "./database_operations.h"

//using namespace std;

//string path = "future_chat1.db";


//int main( int argc, char* argv[] ) {
//    //初始化数据库和SQL语句
//    DataBase db = DataBase( path );
//    string sql;

//    //使用字符串转换查询
//    SelectResult q_res = SelectResult();

//    sql = "select * from user_info";
//    q_res.executeSelect( db, sql );
//    q_res.check_result();
//    //输出查询结果
//    auto a = convert_select_result_to_vector(q_res);
//    cout << a.size()<< endl;
//    for ( int i = 0; i < q_res.row; i++ ) {
//        for ( int j = 0; j < q_res.column; j++ ) {
//            string temp = a[i][j];
//            cout << temp << " ";
//        }
//        cout << endl;
//    }

//}
////删除
////    DeleteResult d_res = DeleteResult();
////    auto sql_ls = vector<string>{
////        "delete from user_info where account=5;",
////            "delete from user_info where account=6;",
////            "delete from user_info where account=7;",
////            "delete from user_info where account=8;"
////        };
////    d_res.batch_executeDelete( db, sql_ls );
////    d_res.check_result();

////    //更新
////    UpdateResult u_res = UpdateResult();
////    sql = "update user_info set password = 'test_update' where account=1";
////    u_res.executeUpdate( db, sql );
////    u_res.check_result();

