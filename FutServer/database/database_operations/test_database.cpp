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

//    //插入
////    InsertResult i_res = InsertResult();
////    sql = "INSERT INTO user_info (password, user_name, signature, gender, birthday, location, education_experience) VALUES ('user123', 'ljy', 'hello!', 'Male', '2002-10-18', 'Beijing', 'BIT');";
////    i_res.executeInsert( db, sql );
////    i_res.check_result();


////    InsertResult i_res = InsertResult();
//////    //批量插入
////    auto sql_ls = vector<string>{
////        "INSERT INTO user_friends (client_account, friend_account, friend_nickname, add_time, status) VALUES (1, 3, 'sunny', '2023-08-28 12:00:00', 1);",
////        "INSERT INTO user_friends (client_account, friend_account, friend_nickname, add_time, status) VALUES (3, 1, 'joy', '2023-08-28 12:00:00', 1);",
////        "INSERT INTO friend_message_library (client_account, friend_account, time, type, content, status) VALUES (1, 3, '2023-08-28 14:33:00', 1, 'Hi!', 0);",
////        "INSERT INTO friend_message_library (client_account, friend_account, time, type, content, status) VALUES (3, 1, '2023-08-28 14:31:00', 1, 'miss u', 0);",
////        "INSERT INTO group_info (group_owner_account, name) VALUES (1, 'futureChat');",
////        "INSERT INTO group_members (group_account, member_account, position, join_time) VALUES (2, 1, 'Master', '2023-08-28 09:00:00');",
////        "INSERT INTO group_members (group_account, member_account, position, join_time) VALUES (2, 3, 'Member', '2023-08-28 09:00:00');",
////        "INSERT INTO group_message_library (group_account, sender_account, time, type, content, status) VALUES (2, 1, '2023-08-28 14:32:10', 1, 'hello sunny!', 0);",
////        "INSERT INTO group_message_library (group_account, sender_account, time, type, content, status) VALUES (2, 3, '2023-08-28 14:32:00', 1, 'hello joy!', 0);"
////        };
////    i_res.batch_executeInsert( db, sql_ls );
////    i_res.check_result();

//    //删除
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

//    //使用字符串转换查询
//    SelectResult q_res = SelectResult();

////    sql = "select gml.group_account AS targetId, false AS targetType, gi.group_avatar_path AS avatar, gml.content AS message, ui.user_name AS msgSender, gml.time AS msgTime FROM group_message_library gml JOIN group_info gi ON gml.group_account = gi.group_account JOIN user_info ui ON gml.sender_account = ui.account JOIN group_members gm ON gml.group_account = gm.group_account AND gm.member_account = 1 ORDER BY msgTime DESC;";

//    sql = "select * from (select gml.group_account AS targetId, gi.name AS targetName, false AS targetType, gi.group_avatar_path AS avatar, gml.content AS message, ui.user_name AS msgSender, gml.time AS msgTime FROM group_message_library gml JOIN group_info gi ON gml.group_account = gi.group_account JOIN user_info ui ON gml.sender_account = ui.account JOIN group_members gm ON gml.group_account = gm.group_account AND gm.member_account = 1 ORDER BY msgTime DESC) GROUP BY targetId;";
////    sql = "SELECT * FROM ("
////            "SELECT "
////            "targetId,"
////            "uii.user_name As targetName,"
////            "targetType,"
////            "uii.avatar_path,"
////            "message,"
////            "msgSender,"
////            "msgTime "
////            "from ("
////                    "SELECT "
////                    "CASE WHEN fml.client_account = 1 THEN fml.friend_account ELSE fml.client_account END AS targetId, "
////                    "true AS targetType,"
////                    "fml.content AS message,"
////                    "CASE WHEN fml.client_account = 1 THEN 'You' ELSE ui.user_name END AS msgSender,"
////                    "fml.time AS msgTime "
////                    "FROM friend_message_library fml "
////                    "JOIN user_info ui ON fml.client_account = ui.account "
////                    "WHERE fml.client_account = 1 OR fml.friend_account = 1) t1 "
////                    "JOIN user_info uii ON t1.targetId = uii.account "
////                    "ORDER BY msgTime DESC) GROUP BY targetId;";

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
