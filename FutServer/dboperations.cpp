#include "futserver.h"
#include "ui_futserver.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QJsonObject FutServer::addAccount(QString userName, QString password)
{
    QJsonObject jsonObj;
    // 插入
    InsertResult insResult = InsertResult();
    QString sql;
    sql = QString("insert into user_info(user_name, password) values ('%1', '%2')").arg(userName, password);
    qDebug() << sql;
    insResult.executeInsert( db, sql.toStdString());

    // 查询注册得到的id
    SelectResult selResult = SelectResult();
    sql = "select max(account) from user_info";
    selResult.executeSelect( db, sql.toStdString());
    auto result = convert_select_result_to_vector(selResult);
    string id = result[0][0];

    jsonObj.insert("request","registerBack"); //反馈类型
    jsonObj.insert("id", QString::fromStdString(id)); // 分配的id
    jsonObj.insert("result",insResult.check_result());// 注册成功与否

    return jsonObj;
}


QJsonObject FutServer::confirmLogin(int clientId, QString password)
{
    QJsonObject jsonObj;
    QString sql;
    sql = QString("select password, user_name from user_info where account = %1").arg(clientId);
    // 查询对应的密码
    SelectResult selResult = SelectResult();
    selResult.executeSelect( db, sql.toStdString());

    auto result = convert_select_result_to_vector(selResult);
//    qDebug() << result.size();
    if(result.size() == 0){
        jsonObj.insert("request","loginBack"); //登录反馈
        jsonObj.insert("result", false);// 密码是否一致
        jsonObj.insert("userName", NULL);
        return jsonObj;
    }
    QString correctPassword= QString::fromStdString(result[0][0]);
    QString userName = QString::fromStdString(result[0][1]);

    jsonObj.insert("request","loginBack"); //登录反馈
    jsonObj.insert("result", correctPassword == password);// 密码是否一致
    jsonObj.insert("userName", userName);

    return jsonObj;
}

inline void swap(QJsonValueRef v1, QJsonValueRef v2)
{
    QJsonValue temp(v1);
    v1 = QJsonValue(v2);
    v2 = temp;
}

QJsonObject FutServer::loadMessageList(int clientId)
{
    QJsonObject jsonObj;
    QJsonArray messages;

    QString sql;
    sql = "SELECT * FROM ("
            "SELECT "
            "targetId,"
            "uii.user_name As targetName,"
            "targetType,"
            "uii.avatar_path,"
            "message,"
            "msgSender,"
            "msgTime "
            "FROM ("
                    "SELECT "
                    "CASE WHEN fml.client_account = 1 THEN fml.friend_account ELSE fml.client_account END AS targetId, "
                    "true AS targetType,"
                    "fml.content AS message,"
                    "CASE WHEN fml.client_account = 1 THEN 'You' ELSE ui.user_name END AS msgSender,"
                    "fml.time AS msgTime "
                    "FROM friend_message_library fml "
                    "JOIN user_info ui ON fml.client_account = ui.account "
                    "WHERE fml.client_account = 1 OR fml.friend_account = 1) t1 "
                    "JOIN user_info uii ON t1.targetId = uii.account "
                    "ORDER BY msgTime DESC) GROUP BY targetId;";

    // 查询私聊信息
    SelectResult selFriendResult = SelectResult();
    selFriendResult.executeSelect( db, sql.toStdString());
    auto friResult = convert_select_result_to_vector(selFriendResult);
    if(friResult.size())
    {
        for ( int i = 0; i < selFriendResult.row; i++ ){
             QJsonObject message;
             message.insert("targetId", QString::fromStdString(friResult[i][0]));
             message.insert("targetName", QString::fromStdString(friResult[i][1]));
             message.insert("targetType", QString::fromStdString(friResult[i][2]));
             message.insert("avatar", QString::fromStdString(friResult[i][3]));
             message.insert("message", QString::fromStdString(friResult[i][4]));
             message.insert("msgSender", QString::fromStdString(friResult[i][5]));
             message.insert("msgTime", QString::fromStdString(friResult[i][6]));
             messages.append(message);
        }
    }

    sql = QString("SELECT * FROM ("
                  "SELECT "
                  "gml.group_account AS targetId, "
                  "gi.name AS targetName, "
                  "false AS targetType, "
                  "gi.group_avatar_path AS avatar, "
                  "gml.content AS message, "
                  "ui.user_name AS msgSender, "
                  "gml.time AS msgTime "
                        "FROM group_message_library gml "
                        "JOIN group_info gi ON gml.group_account = gi.group_account "
                        "JOIN user_info ui ON gml.sender_account = ui.account "
                        "JOIN group_members gm ON gml.group_account = gm.group_account AND gm.member_account = %1 "
                        "ORDER BY msgTime DESC) GROUP BY targetId;").arg(clientId);
    // 查询群聊信息
    SelectResult selGroupResult = SelectResult();
    selGroupResult.executeSelect( db, sql.toStdString());
    auto groupResult = convert_select_result_to_vector(selGroupResult);
    if(groupResult.size())
    {
        for ( int i = 0; i < selGroupResult.row; i++ ){
             QJsonObject message;
             message.insert("targetId", QString::fromStdString(groupResult[i][0]));
             message.insert("targetName", QString::fromStdString(groupResult[i][1]));
             message.insert("targetType", QString::fromStdString(groupResult[i][2]));
             message.insert("avatar", QString::fromStdString(groupResult[i][3]));
             message.insert("message", QString::fromStdString(groupResult[i][4]));
             message.insert("msgSender", QString::fromStdString(groupResult[i][5]));
             message.insert("msgTime", QString::fromStdString(groupResult[i][6]));
             messages.append(message);
        }
    }

    // 按消息时间递减排序
    std::sort(messages.begin(), messages.end(), [](const QJsonValue & v1, const QJsonValue &v2){
        return v1.toObject()["msgTime"].toString() > v2.toObject()["msgTime"].toString();
    });

    jsonObj.insert("request","setHistoryBack");
    jsonObj.insert("messages", messages);

    return jsonObj;
}
