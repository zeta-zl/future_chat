import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluRectangle {
    visible: true
    width: 400
    height: 480

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 80
        id: login
        text: qsTr("登录")
        font.pixelSize: 60
    }
    Column{
        id: col
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: login.bottom
        anchors.topMargin: 30
        spacing: 30


        FluTextBox{
            id: inputid
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText:"账号"
            height: 45
            width: 270
        }

        FluPasswordBox{
            id: inputpwd
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "密码"
            height: 45
            width: 270
        }

    }

    Flow{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: col.bottom
        anchors.topMargin: 45
        spacing: 90

        FluFilledButton{
            width: 90
            height: 45
            text:"登录"
            font.pixelSize: 20

            onClicked: {
                //检查用户账号是否为纯数字
                if(isNaN(inputid.text)){
                    console.log("输入非数字")
                    // 提醒用户只能输入纯数字账号
                    showError("          只能输入纯数字账号")
                }else{
                    userid=inputid.text
                    userpwd=inputpwd.text
                    //发送登录信号
                    console.log(userid,userpwd,"登录")
                    loginSignal(userid,userpwd)
                }

                //点击登录按钮后需要的操作
                //用于服务端未打开时，记得删除

                loginPageLoader.source = "MainPage.qml"
                //var component = Qt.createComponent("MainPage.qml");
                //var win = component.createObject();
                //win.show();
                startPage.visible = false;
            }
        }

        Loader {
            id : loginPageLoader
        }

        FluFilledButton{
            width: 90
            height: 45
            text:"注册"
            font.pixelSize: 20

            onClicked:{
                myLoader.sourceComponent = regPage
                startPage.width = 400
                startPage.height = 560
            }
        }
    }



    // 临时入口
    FluFilledButton{
        width: 90
        height: 45
        text:"聊天"
        font.pixelSize: 20

        onClicked: {
            //点击按钮后需要的操作
            var component = Qt.createComponent("ChatPage.qml");
            var win = component.createObject();
            win.show();
            startPage.visible = false;
        }
    }
}


