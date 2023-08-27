import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow{
    id: chatPage
    width: 800
    height: 650
    title: qsTr("聊天")

    FluRectangle{ // 顶部条
        id: topRtg
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
                                showSuccess("          已开启免打扰")
                            }
                            else{
                                showWarning("          已关闭免打扰")
                            }
                        }
                    }
                },
                FluMenuItem{
                    text:"退出群聊"
                    onClicked: exitDialog.open()
                }
            ]
        }
    }

    ListModel { // 聊天记录列表
            id: chatModel

            // 用户名； 头像； 新消息内容； 是否是自己(暂时以颜色区分)
            ListElement {
                username: "Alice"; avatar: "images/test2.jpg"; message: "Hello!";
                self: false
            }
            ListElement {
                username: "Bob"; avatar: "images/test2.jpg"; message: "Hey there!";
                self: false
            }

            ListElement {
                username: "大黄"; avatar: "images/test3.jpg"; message: "捂脸哭";
                self: true
            }

            ListElement {
                username: "大黄5"; avatar: "images/test2.jpg"; message: "111";
                self: false
            }
    }

    FluRectangle { // 聊天记录区
        id: chatMsgArea
        width: parent.width
        height: 350
        anchors.top: topRtg.bottom

        ScrollView{
            id: chatMsgScrView
            width: parent.width
            height: 350

            ListView{
                id: chatMsgList
                width: parent.width
                height: parent.height
                model: chatModel

                delegate: Item { // 列表元素的结构
                    width: parent.width
                    height: 60

                    Rectangle { // 消息
                        width: parent.width
                        height: 60
                        color: "#F0F0F0"
                        visible: !model.self

                        Text { // 用户名
                            text: model.username
                            font.pixelSize: 14
                            color: "#888888"
                            anchors.top: parent.top
                            anchors.topMargin: 6
                            anchors.left: chatProfilePic.right
                            anchors.leftMargin: 15
                        }

                        Rectangle { // 头像
                            id: chatProfilePic
                            width: 50
                            height: 50
                            radius: 8
                            color: "#F0F0F0"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.left: parent.left
                            anchors.leftMargin: 15

                            Image {
                                width: 50
                                height: 50
                                source: model.avatar
                                mipmap: true // 抗锯齿
                            }
                        }

                        FluCopyableText { // 消息
                            text: model.message
                            font.pixelSize: 18
                            anchors.left: chatProfilePic.right
                            anchors.leftMargin: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10
                        }
                    }

                    Rectangle { // 自己的消息
                        width: parent.width
                        height: 60
                        color: "#4CDF01"
                        visible: model.self

                        Text { // 用户名
                            text: model.username
                            font.pixelSize: 14
                            color: "#888888"
                            anchors.top: parent.top
                            anchors.topMargin: 6
                            anchors.right: chatProfilePicSelf.left
                            anchors.rightMargin: 15
                        }

                        Rectangle { // 头像
                            id: chatProfilePicSelf
                            width: 50
                            height: 50
                            radius: 8
                            color: "#F0F0F0"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.right: parent.right
                            anchors.rightMargin: 15

                            Image {
                                width: 50
                                height: 50
                                source: model.avatar
                                mipmap: true // 抗锯齿
                            }
                        }

                        FluCopyableText { // 消息
                            text: model.message
                            font.pixelSize: 18
                            anchors.right: chatProfilePicSelf.left
                            anchors.rightMargin: 6
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10
                        }
                    }
                }
            }
        }
    }

    property var emojis:
        ["1", "2", "3", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", ""]

    FluMenu{
        id:emojiMenu
        width: 290

        ScrollView {
            width: parent.width
            height: 180

            GridLayout { // 网格布局
                columns: 6 // 指定列数
                width: parent.width
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 10




                Repeater {
                    model: 30

                    Rectangle {
                        height: 40
                        width: 40
                        FluButton{
                            text: emojis[index]
                            height: 40
                            width: 40
                            font.pixelSize: 30

                            onClicked: {

                            }
                        }
                    }
                }
            }
        }
    }

    FluArea {
        id: chatToolsArea
        width: parent.width
        height: 50
        anchors.top: chatMsgArea.bottom

        FluIconButton{
            id: emojiBtn
            iconSource:FluentIcons.EmojiTabSmilesAnimals
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                emojiMenu.popup();
            }
        }

        FluIconButton{
            id: voiceMsgBtn
            iconSource:FluentIcons.MicrophoneListening
            anchors.left: emojiBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {

            }
        }

        FluIconButton{
            id: imgMsgBtn
            iconSource:FluentIcons.ImageExport
            anchors.left: voiceMsgBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {

            }
        }

        FluIconButton{
            id: fileMsgBtn
            iconSource:FluentIcons.Folder
            anchors.left: imgMsgBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {

            }
        }

        FluIconButton{
            id: moreBtn
            iconSource:FluentIcons.Add
            anchors.left: fileMsgBtn.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {

            }
        }
    }

    FluRectangle { //  消息框
        id: chatTextArea
        width: parent.width
        height: {
            if(chatTextBox.height <= 125){
                chatTextBox.height
            }
            else{
                125
            }
        }
        anchors.top: chatToolsArea.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ScrollView{
            width: parent.width
            height: {
                if(chatTextBox.height <= 125){
                    chatTextBox.height
                }
                else{
                    125
                }
            }
            FluArea{
                width: parent.width
                height: chatTextBox.height
                anchors.horizontalCenter: parent.horizontalCenter
                FluMultilineTextBox{
                    id: chatTextBox
                    width: parent.width
                    placeholderText:"请输入消息..."
                    font.pixelSize: 18
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    FluFilledButton {
        text: "发送"
        font.pixelSize: 18
        font.bold: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        onClicked: {
            if(chatTextBox.text === ""){
                showError("          不能发送空消息")
            }
            else{
                chatModel.append({"username": "大黄", "avatar": "images/test3.jpg",
                                 "message": chatTextBox.text, "self": true})
                chatTextBox.clear()
                chatMsgList.positionViewAtEnd() // 保持底部
            }
        }
    }

    FluContentDialog { // 退群确认
        id:exitDialog
        title:"提示"
        message:"确定要退出群聊么？"
        negativeText:"取消"
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onNegativeClicked:{ // 需要接口
            showSuccess("点击取消按钮")
        }
        positiveText:"确定"
        onPositiveClicked:{ // 需要接口
            showSuccess("点击确定按钮")
        }
    }


}
