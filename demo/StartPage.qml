import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0
import QtQuick.Dialogs 1.2

FluWindow {
    id:startPage
    visible: true
    width: 400
    height: 480
    title: qsTr("FutureChat")
    objectName: "startPage_object"

    // 登录信号
    property string userid: ""
    property string userpwd: ""
    signal loginSignal(string userid, string userpwd)

    // 注册信号
    property string regname: ""
    property string regpwd: ""
    property string regpwd2: ""
    signal regSignal(string regname, string regpwd)

    // 请求历史消息信号
    signal requestHistoryMessage(int curuserid)



    // Loader加载不同组件，实现切换页面的功能
    Loader{
        id:myLoader
        anchors.centerIn: parent // 弹出的界面都居中显示
    }
    Component.onCompleted: myLoader.sourceComponent = loginPage // 一开始显示登录页面

    // 2. 登录-Component
    Component{
        id:loginPage
        LoginPage {
            width: 400
            height: 480
            //anchors.centerIn: parent
        }


    }

    // 3.注册-Component
    Component{
        id:regPage
        RegisterPage {
            width: 400
            height: 560
            //anchors.centerIn: parent
        }
    }

    function loginBack(result){
        if(result){
            curuser.id = parseInt(userid)
            //点击登录按钮后需要的操作
            startPageLoader.source = "MainPage.qml"
            requestHistoryMessage(parseInt(userid))
            // var component = Qt.createComponent("MainPage.qml");
            // var win = component.createObject();
            // win.show();
            // startPage.visible = false;
        }else{
            // 失败窗口
        }
    }

    function registerBack(id){
        if(id){
            //注册成功弹出窗口显示id

            //重新回到登陆界面
            myLoader.sourceComponent = loginPage
            startPage.width = 400
            startPage.height = 480
        }else{
            // 失败窗口
        }
    }
    Loader {
           id : startPageLoader
       }
}
