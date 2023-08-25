#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QShortcut>
#include <QDateTime>

Widget::Widget(QWidget *parent, QString f_targetname, int f_targetid, QString f_clientname, int f_clientid)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<"聊天窗启动";
    setAttribute(Qt::WA_DeleteOnClose);

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
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonData = jsonDoc.object();
        QString clientname = jsonData["client_name"].toString();
        QString msg = jsonData["message"].toString();
        QString time = jsonData["timestamp"].toString();
        ui->TextRecord->append(clientname+" "+time+":\n"+msg);
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
    // 获取当前时间并格式化为字符串
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    //创建 JSON 数据串
    QJsonObject jsonData;
    jsonData["client_id"] = clientid;
    jsonData["client_name"] = clientname;
    jsonData["target_client_id"] = targetid;
    jsonData["target_client_name"] = targetname;
    jsonData["message"] = msg;
    jsonData["timestamp"] = formattedTime;

    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(jsonData);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    // 传输 JSON 字符串
    m_tcp->write(jsonString.toUtf8());
    ui->TextRecord->append(clientname+" "+formattedTime+":\n"+msg);
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
    // 获取当前时间并格式化为字符串
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    //创建 JSON 数据串
    QJsonObject jsonData;
    jsonData["client_id"] = clientid;
    jsonData["client_name"] = clientname;
    jsonData["target_client_id"] = targetid;
    jsonData["target_client_name"] = targetname;
    jsonData["message"] = msg;
    jsonData["timestamp"] = formattedTime;

    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(jsonData);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    // 传输 JSON 字符串
    m_tcp->write(jsonString.toUtf8());
}

Widget::~Widget()
{
    qDebug()<<"chatwindow closed";
    delete ui;
    m_tcp->close(); // 关闭连接，触发 disconnected 信号
}





