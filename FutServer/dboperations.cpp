#include "futserver.h"
#include "ui_futserver.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

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
    string id = "0";
    bool insertResult = insResult.check_result();
    if(insertResult){
       qDebug() << "注册成功";
       id = result[0][0];
       qDebug() << QString::fromStdString(id);

       // 注册成功，在数据库中添加自己为好友，(并添加初始聊天记录)
       QString SQLId = QString::fromStdString(id);
       QString nick_name = QString::fromStdString("我");
       QDateTime currentTime = QDateTime::currentDateTime();
       QString addTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
       QString status = QString::fromStdString("1");
       InsertResult addSelfFriend = InsertResult();
       sql = QString("insert into user_friends(client_account, friend_account, friend_nickname"
                     ", add_time, status) values (%1, %2, '%3', '%4', %5)").arg(SQLId, SQLId, nick_name, addTime, status);
       addSelfFriend.executeInsert(db, sql.toStdString());
       qDebug() << sql;
       addSelfFriend.check_result();
    }
    else{
        qDebug() << "注册失败";
    }

    jsonObj.insert("request","registerBack"); //反馈类型
    jsonObj.insert("id", QJsonValue(QString::fromStdString(id).toInt())); // 分配的id,注册失败返回0
    jsonObj.insert("result",QJsonValue(insertResult));// 注册成功与否

    return jsonObj;
}


QJsonObject FutServer::confirmLogin(int clientId, QString password)
{
    QJsonObject jsonObj;
    QJsonObject userInfo;
    QString sql;
    sql = QString("select password, user_name, avatar_path, signature from user_info where account = %1").arg(clientId);
    // 查询对应的密码
    SelectResult selResult = SelectResult();
    selResult.executeSelect( db, sql.toStdString());

    auto result = convert_select_result_to_vector(selResult);

    if(result.size() == 0){
        qDebug() << "登录失败，账号不存在！";
        jsonObj.insert("request",QJsonValue("loginBack")); //登录反馈
        jsonObj.insert("result", QJsonValue(false));//
        jsonObj.insert("userInfo", NULL);
        return jsonObj;
    }

    QString correctPassword= QString::fromStdString(result[0][0]);
    QString userName = QString::fromStdString(result[0][1]);
    QString avatar = QString::fromStdString(result[0][2]);
    QString signature = QString::fromStdString(result[0][3]);
    if(correctPassword == password){
        qDebug() << "登录成功";
    }
    else{
        qDebug() << "密码错误，登陆失败";
    }

    userInfo["userName"] = userName;
    userInfo["avatar"] = avatar;
    userInfo["signature"] = signature;

    jsonObj.insert("request","loginBack"); //登录反馈
    jsonObj.insert("result", QJsonValue(correctPassword == password));// 密码是否一致
    jsonObj.insert("userInfo", QJsonValue(userInfo));

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
    sql = QString("SELECT * FROM ("
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
                    "CASE WHEN fml.client_account = %1 THEN fml.friend_account ELSE fml.client_account END AS targetId, "
                    "true AS targetType,"
                    "fml.content AS message,"
                    "CASE WHEN fml.client_account = %1 THEN 'You' ELSE ui.user_name END AS msgSender,"
                    "fml.time AS msgTime "
                    "FROM friend_message_library fml "
                    "JOIN user_info ui ON fml.client_account = ui.account "
                    "WHERE fml.client_account = %1 OR fml.friend_account = %1) t1 "
                    "JOIN user_info uii ON t1.targetId = uii.account "
                    "ORDER BY msgTime DESC) GROUP BY targetId;").arg(clientId);

    // 查询私聊信息
    SelectResult selFriendResult = SelectResult();
    selFriendResult.executeSelect( db, sql.toStdString());
    if(selFriendResult.check_result())
    {
        qDebug() << "私聊列表初始化成功" ;
    }
    else
    {
        qDebug() << "私聊列表初始化失败" ;
    }
    auto friResult = convert_select_result_to_vector(selFriendResult);

    if(friResult.size())
    {
        for ( int i = 0; i < selFriendResult.row; i++ ){
             QJsonObject message;
             message.insert("targetId", QString::fromStdString(friResult[i][0]));
             message.insert("targetName", QString::fromStdString(friResult[i][1]));
             message.insert("targetType", QJsonValue(true));
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
    if(selGroupResult.check_result())
    {
        qDebug() << "群聊列表初始化成功" ;
    }
    else
    {
        qDebug() << "群聊列表初始化失败" ;
    }
    auto groupResult = convert_select_result_to_vector(selGroupResult);
    if(groupResult.size())
    {
        for ( int i = 0; i < selGroupResult.row; i++ ){
             QJsonObject message;
             message.insert("targetId", QString::fromStdString(groupResult[i][0]).toInt());
             message.insert("targetName", QString::fromStdString(groupResult[i][1]));
             message.insert("targetType", QJsonValue(false));
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

    setFriendsGroupsList(clientId, messages);

    return jsonObj;
}

void FutServer::setFriendsGroupsList(int clientId, QJsonArray messages)
{
    QJsonArray friendList;
    QJsonArray groupList;

    for(int i = 0; i < messages.size() ;i++)
    {
        if(messages.at(i)["targetType"] == true) // 好友
        {
            friendList.append(messages.at(i));
        }
        else // 群聊
        {
            groupList.append(messages.at(i));
        }
    }

    QJsonObject* userMessages = new QJsonObject;
    userMessages->insert("messages", messages);
    userMessages->insert("friendList", friendList);
    userMessages->insert("groupList", groupList);
    clientMessages.insert(clientId, userMessages);
    qDebug() << "已初始化界面用户数量： " << clientMessages.size() << " 好友数量："<< friendList.size() <<  " 群聊数量：" << groupList.size();
}


// 保存聊天记录到数据库
QJsonObject FutServer::saveMessage(int clientId, int targetId, bool targetType, QString content, QString time)
{
    QJsonObject jsonObj;
    // 插入
    InsertResult insResult = InsertResult();
    SelectResult selResult = SelectResult();
    QString sql;
    if(targetType == true) // 私聊信息  消息类型和状态目前默认为1
    {
        sql = QString("insert into friend_message_library(client_account, friend_account, time, type, content, status) "
                      "values (%1, %2,'%3', %4,'%5', %6)").arg(QString::number(clientId), QString::number(targetId), time, "1", content, "1");
    }
    else // 群聊信息
    {
        sql = QString("insert into group_message_library(group_account, sender_account, time, type, content, status) "
                      "values (%1, %2,'%3', %4,'%5', %6)").arg(QString::number(targetId), QString::number(clientId), time, "1", content, "1");
    }

    qDebug() << sql;
    insResult.executeInsert( db, sql.toStdString());
    bool insertResult = insResult.check_result();

    sql = QString("SELECT user_name, avatar_path FROM user_info WHERE account = %1").arg(clientId);
    selResult.executeSelect( db, sql.toStdString());
    auto searchResult = convert_select_result_to_vector(selResult);
    QString senderName;
    QString senderAvatar;
    if(searchResult.size())
    {
        senderName = QString::fromStdString(searchResult[0][0]);
        senderAvatar = QString::fromStdString(searchResult[0][1]);
    }


    if(insertResult){
        if(targetType){ // 私聊 groupId为0
            jsonObj.insert("request", "sendChatMessageBack");
            jsonObj.insert("groupId", QJsonValue(0));
            jsonObj.insert("senderId", QJsonValue(clientId));
            jsonObj.insert("senderName", QJsonValue(senderName));
            jsonObj.insert("senderAvatar", QJsonValue(senderAvatar));
            jsonObj.insert("content",QJsonValue(content));
            jsonObj.insert("time", QJsonValue(time));
        }
        else{ // 群聊
            jsonObj.insert("request", "sendChatMessageBack");
            jsonObj.insert("groupId", QJsonValue(targetId));
            jsonObj.insert("senderId", QJsonValue(clientId));
            jsonObj.insert("senderName", QJsonValue(senderName));
            jsonObj.insert("senderAvatar", QJsonValue(senderAvatar));
            jsonObj.insert("content",QJsonValue(content));
            jsonObj.insert("time", QJsonValue(time));
        }
    }
    else{
        qDebug() << "保存聊天记录失败";
    }
    return jsonObj;
}

QList<int> FutServer::getGroupMemberList(int groupId)
{
    QList<int> groupMemberList;
    SelectResult selResult = SelectResult();
    QString sql = QString("select member_account from group_members where group_account = %1").arg(groupId);
    selResult.executeSelect( db, sql.toStdString());
    auto groupMemberListResult = convert_select_result_to_vector(selResult);

    if(selResult.check_result() && groupMemberListResult.size())
    {
        for(int i = 0; i < selResult.row ; i++){
            for(int j = 0 ; j < selResult.column ; j++){
                int memberId = QString::fromStdString(groupMemberListResult[i][j]).toInt();
                groupMemberList.append(memberId);
            }
        }
    }
    else{
        qDebug() << "未找到群成员";
    }
    return groupMemberList;
}


QJsonObject FutServer::getHistoryMessage(int clientId, int targetId, bool targetType)
{
    QJsonObject jsonObj;
    QJsonArray messages;
    QString sql;
    SelectResult selResult = SelectResult();

    if(targetType) // 私聊
    {
        sql = QString("SELECT client_account AS senderId, user_name As senderName, avatar_path AS senderAvatar, content, time, type, status, id "
                      "FROM friend_message_library JOIN user_info ON friend_message_library.client_account = user_info.account "
                      "WHERE (client_account = %1 AND friend_account = %2) "
                      "OR (client_account = %2 AND friend_account = %1) ORDER BY id DESC").arg(QString::number(clientId), QString::number(targetId));
    }
    else // 群聊
    {
        sql = QString("SELECT sender_account AS senderId, user_name As senderName, avatar_path AS senderAvatar, content, time, type, status, id "
                      "FROM group_message_library JOIN user_info ON group_message_library.sender_account = user_info.account "
                      "WHERE group_account = %1 ORDER BY id DESC").arg(QString::number(targetId));
    }

    selResult.executeSelect(db, sql.toStdString());
    auto msgResult = convert_select_result_to_vector(selResult);

    if(selResult.check_result() && msgResult.size()) // 查询成功且有历史消息
    {
        for(int i = 0; i < selResult.row ; i++)
        {
            QJsonObject message;
            message.insert("senderId", QString::fromStdString(msgResult[i][0]).toInt());
            message.insert("senderName", QString::fromStdString(msgResult[i][1]));
            message.insert("senderAvatar", QString::fromStdString(msgResult[i][2]));
            message.insert("content", QString::fromStdString(msgResult[i][3]));
            message.insert("time", QString::fromStdString(msgResult[i][4]));
            message.insert("type", QString::fromStdString(msgResult[i][5]).toInt());
            message.insert("status", QString::fromStdString(msgResult[i][6]).toInt());
            messages.append(message);
        }
    }
    else
    {
        qDebug() << "查询历史消息失败或不存在历史消息";
    }

    jsonObj.insert("request", "initChatWindowBack");
    jsonObj.insert("messages", messages);
    jsonObj.insert("targetId", targetId);
    jsonObj.insert("targetType", targetType);
    jsonObj.insert("msgNumber",selResult.row);
    return jsonObj;
}

QJsonObject FutServer::getTargetMessageList(int clientId, bool targetType)
{
    QJsonObject jsonObj;
    jsonObj["request"] = "setFriendsBack";
    jsonObj["targetType"] = targetType;
    QJsonArray messages;
    QJsonObject userMsg = *clientMessages.value(clientId);
    if(targetType == true)
    {
        jsonObj["messages"] = userMsg["friendList"];
    }
    else{
        jsonObj["messages"] = userMsg["groupList"];
    }
    return jsonObj;
}
