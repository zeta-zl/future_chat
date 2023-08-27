#include "userinfo.h"

userinfo::userinfo()
{

}

int userinfo::getId(){
    return m_id;
}

void userinfo::setId(int id){
    if(m_id!=id){
        m_id=id;
        emit idchanged();
    }
}

QString userinfo::getName(){
    return m_name;
}

void userinfo::setName(QString name){
    if(m_name!=name){
        m_name=name;
        emit namechanged();
    }
}

void userinfo::parse(QJsonObject jsonobject){
    m_id=jsonobject["id"].toInt();
    m_name=jsonobject["name"].toString();
    qDebug()<<"userinfo"<<m_id<<m_name;
}
