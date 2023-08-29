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

    FluWindow {
        id: loginFailWin
        width: 300
        height: 200
        launchMode: FluWindow.Standard
    }

    function loginBack(result){
        if(result){
            //点击登录按钮后需要的操作
            startPageLoader.source = "MainPage.qml"
            // var component = Qt.createComponent("MainPage.qml");
            // var win = component.createObject();
            // win.show();
            startPage.visible = false;
        }else{
            // 失败窗口
            loginFailDialog.open()
        }
    }

    Loader {
        id : startPageLoader
    }

    function registerBack(id){
        console.log("qml registerBack is called")
        if(id){
            //成功显示id
            regDialog.open()


            //显示登陆界面
            myLoader.sourceComponent = loginPage
            startPage.width = 400
            startPage.height = 480
        }else{
            // 失败窗口
            regFailDialog.open()
        }
    }

    FluContentDialog {
        id:regDialog
        title:"注册成功！"
        message:"您的ID为："
        buttonFlags: FluContentDialog.PositiveButton
        positiveText:"确定"
        onPositiveClicked:{
            myLoader.sourceComponent = loginPage
        }
    }

    FluContentDialog {
        id:regFailDialog
        title:"注册失败！"
        message:"请重试..."
        buttonFlags: FluContentDialog.PositiveButton
        positiveText:"确定"
        onPositiveClicked:{
            myLoader.sourceComponent = regPage
        }
    }

    FluContentDialog {
        id:loginFailDialog
        title:"登录失败！"
        message:"请检查网络后重试..."
        buttonFlags: FluContentDialog.PositiveButton
        positiveText:"确定"
        onPositiveClicked:{
            myLoader.sourceComponent = loginPage
        }
    }
}
