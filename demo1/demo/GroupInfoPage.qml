import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow{
    id: groupInfoWin
    width: 300
    height: 500
    launchMode: FluWindow.SingleInstance

    Item{
        width: parent.width
        height: parent.height

        Rectangle { // 头像
            id: groupAvatar
            width: 150
            height: 150
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
        }

        ColumnLayout{
            width: 200
            anchors.top: groupAvatar.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 50
            spacing: 10

            FluText {
                width: 200
                text: qsTr("群名称:")
                font.pixelSize: 16
            }

            FluText{
                width: 200

                text: qsTr("群号：")
                font.pixelSize: 16
            }

            Item{ // 有小bug
                width: 200
                height: 100

                ScrollView {
                    width: 200
                    height: 100
                    clip: true

                    Text {
                        width: 200
                        text: qsTr("群公告：这是一个群公告。群公告被设置为不可复制。公告如果太长，可以滑动显示。请所有人......。0000000000000000000000000000000000000。。。。。。。。。。")
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.pixelSize: 16
                    }
                }
            }
        }

        FluFilledButton{
            text: "完成"
            font.pixelSize: 18
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                groupInfoWin.close()
            }
        }
    }
}
