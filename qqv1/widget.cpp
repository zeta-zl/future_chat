#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QShortcut>

Widget::Widget(QWidget *parent, QString f_targetname, int f_targetid, QString f_clientname, int f_clientid)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    targetname = f_targetname;
    targetid = f_targetid;
    clientname = f_clientname;
    clientid = f_clientid;
    m_port=8899;
    m_ip = "127.0.0.1";

    m_tcp = new QTcpSocket(this);
    c_connectServer();
    start();
    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_tcp->readAll();
        ui->TextRecord->append("服务器:"+data);
    });
}

void Widget::closeEvent(QCloseEvent *){
    emit this->closeWidget();
}

void Widget::c_connectServer(){
    unsigned short port =m_port;
    m_tcp->connectToHost(QHostAddress(m_ip),port);
}

void Widget::on_sendBtn_clicked()
{
    //向服务器传递id name msg
    QString msg = ui->msgTextEdit->toPlainText();
    if (msg == ""){
        QMessageBox::warning(this,"警告","发送内容不能为空");
        return;
    }
    //创建 JSON 数据串
    QJsonObject jsonData;
    jsonData["client_id"] = clientid;
    jsonData["client_name"] = clientname;
    jsonData["target_client_id"] = targetid;
    jsonData["target_client_name"] = targetname;
    jsonData["message"] = msg;

    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(jsonData);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    // 传输 JSON 字符串
    m_tcp->write(jsonString.toUtf8());
    ui->TextRecord->append(targetname+":"+msg);
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
}

void Widget::on_backBtn_clicked()
{
    this->close();
}

void Widget::start(){
    //向服务器传递id name msg
    QString msg = "start client";
    //创建 JSON 数据串
    QJsonObject jsonData;
    jsonData["client_id"] = clientid;
    jsonData["client_name"] = clientname;
    jsonData["target_client_id"] = targetid;
    jsonData["target_client_name"] = targetname;
    jsonData["message"] = msg;
    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(jsonData);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    // 传输 JSON 字符串
    m_tcp->write(jsonString.toUtf8());
}

Widget::~Widget()
{
    delete ui;
    emit chatWindowClosed(clientid);
}





