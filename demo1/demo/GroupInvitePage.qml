import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow{
    id: groupMemberWin
    title: "邀请好友"
    width: 300
    height: 650
    launchMode: FluWindow.SingleInstance

    ListModel { // 聊天记录列表
            id: memberModel

            // 用户名； 头像
            ListElement {
                username: "Alice"; avatar: "images/test2.jpg";
            }
            ListElement {
                username: "Bob"; avatar: "images/test2.jpg";
            }

            ListElement {
                username: "大黄"; avatar: "images/test3.jpg";
            }
    }

    ListView {
                width: parent.width
                height: parent.height
                clip: true
                model: memberModel
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                }
                delegate: Item {
                    width: parent.width
                    height: 80

                    Rectangle { // 联系人条
                        id: item
                        property bool isHover: false

                        width: parent.width
                        height: 80
                        color: isHover == true ? "#DDDDDD" : Qt.rgba(251/255,251/255,253/255,1)
                        state: isHover
                        MouseArea{
                            enabled: true
                            onClicked: {

                            }
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                item.isHover = true
                            }
                            onExited: {
                                item.isHover = false
                            }

                        }
                        states: [
                                        State { name: "true"; PropertyChanges { target: item; color : "#DDDDDD" } },
                                        State { name: "false"; PropertyChanges { target: item; color : Qt.rgba(251/255,251/255,253/255,1) }}
                        ]
                        transitions: [
                                        Transition { ColorAnimation { to: "#DDDDDD"; duration: 80 } },
                                        Transition { ColorAnimation { to: Qt.rgba(251/255,251/255,253/255,1); duration: 80  } }
                        ]
                        Rectangle // 头像
                        {
                            id:profilePic
                            width: 60
                            height: 60
                            radius: 8
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.left: parent.left
                            anchors.leftMargin: 5

                            Image {
                                id: image
                                width: 60
                                height: 60
                                source: model.avatar
                                mipmap: true // 抗锯齿
                            }
                        }

                        Text {
                            text: model.username
                            font.pixelSize: 18
                            anchors.top: parent.top
                            anchors.topMargin: 15
                            anchors.left: profilePic.right
                            anchors.leftMargin: 20
                        }
                    }
                }
            }
    }
