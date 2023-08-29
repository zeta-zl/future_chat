
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluRectangle {
    visible: true
    width: 400
    height: 560
    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 80
        id: login
        text: qsTr("注册")
        font.pixelSize: 60
    }
    Column{
        id: col
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: login.bottom
        anchors.topMargin: 30
        spacing: 30


        FluTextBox{
            id:name
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText:"用户名"
            height: 45
            width: 270
        }

        FluPasswordBox{
            id:pwd
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "密码"
            height: 45
            width: 270
        }

        FluPasswordBox{
            id:pwd2
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "确认密码"
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
            text:"注册"
            font.pixelSize: 20
            onClicked: {
                regname=name.text
                regpwd=pwd.text
                regpwd2=pwd2.text

                if(regpwd!=regpwd2){
                    // 弹出两次密码不匹配提示框
                    showError("          两次密码不匹配")
                }else if(regname==""){
                    // 弹出用户名不能为空提示框
                    showError("          用户名不能为空")
                }else if(regpwd==""){
                    // 弹出密码不能为空提示框
                    showError("          密码不能为空")
                }else{
                    console.log(regname,regpwd,"注册")
                    regSignal(regname,regpwd);
                }
            }
        }

        FluFilledButton{
            width: 90
            height: 45
            text:"取消"
            font.pixelSize: 20
            onClicked: {
                myLoader.sourceComponent = loginPage
                startPage.width = 400
                startPage.height = 480
            }
        }
    }

}
