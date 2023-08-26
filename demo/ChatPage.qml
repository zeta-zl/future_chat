import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow{
    id:chatPage
    width: 1000
    height: 800
    title: qsTr("聊天")



    FluRectangle{ // 顶部条
        width: parent.width
        height: 70
        color: "#F0F0F0"



        FluIconButton{
            id: backBtn
            iconSource:FluentIcons.Back
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                var component = Qt.createComponent("MainPage.qml");
                var win = component.createObject();
                win.show();
                chatPage.visible = false;
            }
        }

        Text {
            anchors.left: backBtn.right
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 5
            text: qsTr("生于未来")  // 需要接口
            font.pixelSize: 30
        }

        Text {
            anchors.left: backBtn.right
            anchors.leftMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: qsTr("6人")  // 需要接口
            font.pixelSize: 18
            color: "#888888"
        }

        FluDropDownButton{
            text:"       菜单       "
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter


            items:[
                FluMenuItem{
                    text:"查看群名片"
                },
                FluMenuItem{
                    text:"查看群成员"
                },
                FluMenuItem{
                    text:"邀请好友"
                },
                FluMenuItem{
                    FluToggleButton{
                        text:"消息免打扰"
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            selected = !selected
                            if(selected === true){
                                showSuccess("已开启免打扰")
                            }
                            else{
                                showWarning("已关闭免打扰")
                            }
                        }
                    }
                },
                FluMenuItem{
                    text:"退出群聊"
                }
            ]
        }
    }
}
