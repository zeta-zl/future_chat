import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0


FluWindow {
    id: root
    visible: true
    width: 400
    height: 480
    title: qsTr("Login")
    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 80
        id: login
        text: qsTr("login")
        font.pixelSize: 60
    }
    Column{
        id: col
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: login.bottom
        anchors.topMargin: 30
        spacing: 30


        FluTextBox{
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText:"id"
            height: 45
            width: 270
        }

        FluPasswordBox{
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "password"
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

            }
        }

        FluFilledButton{
            width: 90
            height: 45
            text:"注册"
            font.pixelSize: 20
            onClicked: {

            }
        }
    }

}
