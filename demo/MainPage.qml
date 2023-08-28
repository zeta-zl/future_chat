import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow {
    id:mainPage
    visible: true
    width: 400
    height: 800
    title: qsTr("FutureChat")
    objectName: "mainPage_object"

    // 请求历史消息
    signal requestHistoryMessage(int curuserid)


    ListModel {
            id: friendModel  

            // 用户名； 头像； 新消息内容； 新消息数量； 是否开启免打扰
            ListElement {
                username: "Alice"; avatar: "images/test.png"; message: "Hello!";
                newmsg: "3"; newmsgtime: "三天前"; isdonotdisturb: false
            }
            ListElement {
                username: "Bob"; avatar: "images/test.png"; message: "Hey there!";
                newmsg: "100"; newmsgtime: "2021/8/24"; isdonotdisturb: false
            }

            ListElement {
                username: "生于未来"; avatar: "images/test.png"; message: "大黄：[捂脸哭]";
                newmsg: "100"; newmsgtime: "19:40"; isdonotdisturb: true
            }
    }

    function sendRequest() {
      requestHistoryMessage(curuser.id);
    }

    ListView {
        width: parent.width
        height: parent.height
        model: friendModel
        delegate: Item {
            id: item
            width: parent.width
            height: 80

            Rectangle { // 联系人条
                width: parent.width
                height: 80
                color: "#F0F0F0"

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

                    FluBadge{
                        count: model.newmsg // 圆点数字
                        isDot: model.isdonotdisturb
                        color: Qt.rgba(255/255,0/255,0/255,1)
                    }

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

                Text {
                    text: model.message
                    font.pixelSize: 15
                    color: "#888888"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 15
                    anchors.left: profilePic.right
                    anchors.leftMargin: 20
                }

                Text {
                    text: model.newmsgtime
                    font.pixelSize: 15
                    color: "#888888"
                    anchors.top: parent.top
                    anchors.topMargin: 15
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                }
            }
        }
    }
}
