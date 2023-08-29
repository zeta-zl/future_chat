import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0
import QtGraphicalEffects 1.0

FluWindow {
    id: root
    visible: true
    width: 400
    height: 800
    //backgroundColor: "white"
    title: qsTr("FutureTalk")
    objectName: "MainPage_object"

    function setHistoryBack(chatName,avatar,message,msgSender,timestamp) {
            console.log(chatName,avatar,message,msgSender,timestamp)
            friendModel.append({"username": chatName, "avatar": "images/test.png", "message": msgSender+":"+message,
                                "newmsg": "3", "newmsgtime": timestamp, "isdonotdisturb": false})
        }

//        function setHistoryBack(chatName,avatar,message,msgSender,timestamp) {
//           var e{
//                username: chatName; avatar: "images/test.png"; message: msgSender+":"+message;
//                newmsg: "3"; newmsgtime: timestamp; isdonotdisturb: false;
//            };
//            friendModel.append(e);
//        }

//    ListModel {
//            id: friendModel

//    function setHistoryBack(chatName,avatar,message,msgSender,timestamp) {
//        console.log(chatName,avatar,message,msgSender,timestamp)
//        friendModel.append({"username": chatName, "avatar": "images/test.png", "message": msgSender+":"+message,
//                            "newmsg": "3", "newmsgtime": timestamp, "isdonotdisturb": false
//                           })
//    }

    ListModel {
            id: friendModel
            // 用户名； 头像； 新消息内容； 新消息数量； 是否开启免打扰; 是否是群聊
            ListElement {
                username: "Alice"; avatar: "images/test2.jpg"; message: "Hello!";
                newmsg: "3"; newmsgtime: "三天前"; isdonotdisturb: false;
                isgroup: false
            }
//            ListElement {
//                username: "Bob"; avatar: "images/test2.jpg"; message: "Hey there!";
//                newmsg: "100"; newmsgtime: "2021/8/24"; isdonotdisturb: false
//            }
    }

    ListModel {
            id: groupModel
            // 用户名； 头像； 新消息内容； 新消息数量； 是否开启免打扰; 是否是群聊; 群聊人数
            ListElement {
                username: "sywl"; avatar: "images/test2.jpg"; message: "Hello!";
                newmsg: "3"; newmsgtime: "三天前"; isdonotdisturb: false;
                isgroup: true; groupmember: "10"
            }
//            ListElement {
//                username: "Bob"; avatar: "images/test2.jpg"; message: "Hey there!";
//                newmsg: "100"; newmsgtime: "2021/8/24"; isdonotdisturb: false
//            }
    }



    FluArea {
        color: Qt.rgba(251/255,251/255,253/255,1)
        anchors.top: parent.top
        id: userCard
        width: 400
        height: 120
        Rectangle // 头像
        {
            id: userPic
            border.color: "black"
            border.width: 10
            width: 80
            height: 80
            anchors.verticalCenter: parent.verticalCenter
            anchors.bottomMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 15
            Image {
                width: 80
                height: 80
                source: "images/test3.jpg"
                mipmap: true // 抗锯齿
            }
            MouseArea{
                enabled: true
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    overTimer.stop();
                    if (subWindow.visible === true) return;
                    subWindow.opacity = 0.0;
                    subWindow.visible = true;
                    downAnimation.start();
                    showAnimation.start();
                }
                onExited: {
                    overTimer.start();
                }

            }
            layer.enabled : true
            layer.effect: DropShadow {
                transparentBorder: true
                color: "black"
                samples: 20
            }
        }
        Text {
            id: userName
            text: qsTr("用户名")
            font.pixelSize: 30
            font.bold: true
            anchors.top: userPic.top
            anchors.left: userPic.right
            anchors.leftMargin: 30
        }
        Text {
            text: qsTr("这里是一条个性签名.")
            anchors.left: userName.left
            anchors.top: userName.bottom
            anchors.topMargin: 10
        }
        FluIconButton {
            iconSource: FluentIcons.Add
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
            width: 30
            height: 30
            onClicked: {
                var component = Qt.createComponent("AddPage.qml");
                var win = component.createObject(root);
                win.show();
            }
        }
    }
    PopPage {
        id: subWindow
        visible: false
        x: root.x - subWindow.width -6
        y: root.y
        height: 200
        width: 300
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                overTimer.stop();
            }
            onExited: {
                overTimer.start();
            }
        }
    }
    Timer{
        id: overTimer
        interval: 500
        repeat: false
        onTriggered: {
            upAnimation.start();
            hideAnimation.start();
        }
    }

    PropertyAnimation{
        id: showAnimation
        target: subWindow
        properties:"opacity"
        from: 0.0
        to: 1.0
        duration: 250
    }

    PropertyAnimation{
        id: hideAnimation
        target: subWindow
        properties:"opacity"
        from: 1.0
        to: 0.0
        duration: 250
        onStopped: {
            subWindow.visible = false;
        }
    }

    PropertyAnimation{
        id: downAnimation
        target: subWindow
        properties:"y"
        from: root.y
        to: root.y + 24
        duration: 150
    }

    PropertyAnimation{
        id: upAnimation
        target: subWindow
        properties:"y"
        from: root.y + 24
        to: root.y
        duration: 150
    }
    FluPivot {
        anchors.top: userCard.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 400
        height: 800
        currentIndex: 0
        FluPivotItem{
            title:"    消息   "
            contentItem:ListView {
                width: parent.width
                height: parent.height
                clip: true
                model: friendModel
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
                                var component = Qt.createComponent("ChatPage.qml");
                                var win = component.createObject(root);
                                win.show();
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

                            FluBadge{
                                z:99
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
        FluPivotItem{
            title:"   联系人   "
            contentItem:ListView {
                width: parent.width
                height: parent.height
                clip: true
                model: friendModel
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                }
                delegate: Item {

                    width: parent.width
                    height: 80

                    Rectangle { // 联系人条
                        id: item_
                        property bool isHover: false

                        width: parent.width
                        height: 80
                        color: isHover == true ? "#DDDDDD" : Qt.rgba(251/255,251/255,253/255,1)
                        state: isHover
                        MouseArea{
                            enabled: true
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: item_.isHover = true
                            onExited: item_.isHover = false
                            onDoubleClicked: {
                                var component = Qt.createComponent("ChatPage.qml");
                                var win = component.createObject(root);
                                win.show();
                            }
                        }
                        states: [
                                        State { name: "true"; PropertyChanges { target: item_; color : "#DDDDDD" } },
                                        State { name: "false"; PropertyChanges { target: item_; color : Qt.rgba(251/255,251/255,253/255,1) }}
                        ]
                        transitions: [
                                        Transition { ColorAnimation { to: "#DDDDDD"; duration: 80 } },
                                        Transition { ColorAnimation { to: Qt.rgba(251/255,251/255,253/255,1); duration: 80  } }
                        ]
                        Rectangle // 头像
                        {
                            id:profilePic_
                            width: 60
                            height: 60
                            radius: 8
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.left: parent.left
                            anchors.leftMargin: 5

                            FluBadge{
                                z:99
                                count: model.newmsg // 圆点数字
                                isDot: model.isdonotdisturb
                                color: Qt.rgba(255/255,0/255,0/255,1)
                            }

                            Image {
                                id: image_
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
                            anchors.left: profilePic_.right
                            anchors.leftMargin: 20
                        }

//                        Text {
//                            text: model.message
//                            font.pixelSize: 15
//                            color: "#888888"
//                            anchors.bottom: parent.bottom
//                            anchors.bottomMargin: 15
//                            anchors.left: profilePic.right
//                            anchors.leftMargin: 20
//                        }

//                        Text {
//                            text: model.newmsgtime
//                            font.pixelSize: 15
//                            color: "#888888"
//                            anchors.top: parent.top
//                            anchors.topMargin: 15
//                            anchors.right: parent.right
//                            anchors.rightMargin: 15
//                        }
                    }
                }
            }
        }
        FluPivotItem{
            title:"  群聊  "
            contentItem:ListView {
                width: parent.width
                height: parent.height
                clip: true
                model: groupModel
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                }
                delegate: Item {

                    width: parent.width
                    height: 80

                    Rectangle { // 联系人条
                        id: item2_
                        property bool isHover: false

                        width: parent.width
                        height: 80
                        color: isHover == true ? "#DDDDDD" : Qt.rgba(251/255,251/255,253/255,1)
                        state: isHover
                        MouseArea{
                            enabled: true
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: item2_.isHover = true
                            onExited: item2_.isHover = false
                            onDoubleClicked: {
                                var component = Qt.createComponent("ChatPage.qml");
                                var win = component.createObject(root);
                                win.show();
                            }
                        }
                        states: [
                                        State { name: "true"; PropertyChanges { target: item2_; color : "#DDDDDD" } },
                                        State { name: "false"; PropertyChanges { target: item2_; color : Qt.rgba(251/255,251/255,253/255,1) }}
                        ]
                        transitions: [
                                        Transition { ColorAnimation { to: "#DDDDDD"; duration: 80 } },
                                        Transition { ColorAnimation { to: Qt.rgba(251/255,251/255,253/255,1); duration: 80  } }
                        ]
                        Rectangle // 头像
                        {
                            id:profilePic2_
                            width: 60
                            height: 60
                            radius: 8
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.left: parent.left
                            anchors.leftMargin: 5

                            FluBadge{
                                z:99
                                count: model.newmsg // 圆点数字
                                isDot: model.isdonotdisturb
                                color: Qt.rgba(255/255,0/255,0/255,1)
                            }

                            Image {
                                id: image2_
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
                            anchors.left: profilePic2_.right
                            anchors.leftMargin: 20
                        }

//                        Text {
//                            text: model.message
//                            font.pixelSize: 15
//                            color: "#888888"
//                            anchors.bottom: parent.bottom
//                            anchors.bottomMargin: 15
//                            anchors.left: profilePic.right
//                            anchors.leftMargin: 20
//                        }

//                        Text {
//                            text: model.newmsgtime
//                            font.pixelSize: 15
//                            color: "#888888"
//                            anchors.top: parent.top
//                            anchors.topMargin: 15
//                            anchors.right: parent.right
//                            anchors.rightMargin: 15
//                        }
                    }
                }
            }
        }
    }
}
