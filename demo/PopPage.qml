import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0
import QtGraphicalEffects 1.0

FluWindow {
    flags: Qt.FramelessWindowHint
    Text {
        id: name
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 30
        text: qsTr("username(id)")
        font.pixelSize: 32
        font.bold: true
    }
    Text {
        id: age
        text: qsTr("20岁")
        anchors.rightMargin: 20
        anchors.verticalCenter: sex.verticalCenter
        anchors.left: sex.right
        anchors.leftMargin: 20
        font.pixelSize: 20
    }
    Text {
        id: sig
        anchors.top: name.bottom
        anchors.topMargin: 50
        text: qsTr("个性签名")
        anchors.left: name.left
        font.pixelSize: 20
        font.italic: true
    }
    Text {
        id: sex
        anchors.right: parent.right
        anchors.rightMargin: 70
        anchors.verticalCenter: sig.verticalCenter
        text: qsTr("男")
        font.pixelSize: 20
    }
}
