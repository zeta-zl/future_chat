import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow{
    id: chatPage
    width: 800
    height: 850
    title: qsTr("聊天")
    objectName: "chatPage_object"

    function createChatPageBack(senderId,content,time,type,status){
        console.log("function createChatPageBack() ")
        console.log(curuser.id)
        if(senderId !== curuser.id){
            chatModel.append({"username": "Bob", "avatar": "images/test2.jpg",
                               "message": content,"self": false})
        }else{
            chatModel.append({"username": "Bob", "avatar": "images/test2.jpg",
                               "message": content,"self": true})
        }
    }

    signal sendChatMessagefunc(QString clientId, QString targetId, QString targetType, QString content, QString time)


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
                chatPage.close()
            }
        }

        Text {
            anchors.left: backBtn.right
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 5
            text: model.username
            font.pixelSize: 30
        }

        Text {
            anchors.left: backBtn.right
            anchors.leftMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: {
                if(model.isgroup){
                    model.groupmember + "人"
                }
            }

            font.pixelSize: 18
            color: "#888888"
        }



        FluDropDownButton{
            text:"       菜单       "
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            visible: model.isgroup


            items:[
                FluMenuItem{
                    text:"查看群名片"

                    onClicked: {
                         var component = Qt.createComponent("GroupInfoPage.qml");
                         var win = component.createObject(chatPage);
                         win.show();
                    }
                },
                FluMenuItem{
                    text:"查看群成员"
                    onClicked: {
                        var component = Qt.createComponent("GroupMemberPage.qml");
                        var win = component.createObject(chatPage);
                        win.show();
                    }
                },
                FluMenuItem{
                    text:"邀请好友"
                    onClicked: {
                        var component = Qt.createComponent("GroupInvitePage.qml");
                        var win = component.createObject(chatPage);
                        win.show();
                    }
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

//            // 用户名； 头像； 新消息内容； 是否是自己(暂时以颜色区分)
//            ListElement {
//                username: "Alice"; avatar: "images/test2.jpg"; message: "1";
//                self: false
//            }
//            ListElement {
//                username: "Bob"; avatar: "images/test2.jpg"; message: "捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭捂脸哭";
//                self: false
//            }

//            ListElement {
//                username: "大黄5"; avatar: "images/test2.jpg"; message: "111";
//                self: false
//            }
    }

    FluRectangle { // 聊天记录区
        id: chatMsgArea
        width: parent.width
        height: 550
        anchors.top: topRtg.bottom

        ScrollView{
            id: chatMsgScrView
            width: parent.width
            height: 550

            ListView{
                id: chatMsgList
                width: parent.width
                height: parent.height
                model: chatModel

                delegate: ColumnLayout { // 列表元素的结构
                    width: parent.width

                    Rectangle { // 别人的消息
                        width: parent.width
                        height: {
                            if(chatMsgText.height <= 25){
                                80
                            }
                            else{
                                chatMsgText.height + 60
                            }
                        }
                        visible: !model.self

                        Text { // 用户名
                            text: model.username
                            font.pixelSize: 16
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
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.left: parent.left
                            anchors.leftMargin: 15

                            Image {
                                width: 50
                                height: 50
                                source: model.avatar
                                mipmap: true // 抗锯齿
                            }
                        }

                        Rectangle{
                            width: chatMsgText.width + 20
                            height: chatMsgText.height + 20
                            radius: 8
                            color: "#F0F0F0"
                            anchors.left: chatProfilePic.right
                            anchors.leftMargin: 15
                            anchors.top: parent.top
                            anchors.topMargin: 30

                            FluCopyableText { // 消息
                                id: chatMsgText
                                text: model.message
                                width: {
                                    if(chatMsgText2.width >= 380) {380}
                                }
                                wrapMode: Text.WrapAnywhere
                                font.pixelSize: 18
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }

                    Rectangle { // 自己的消息
                        width: parent.width
                        height: {
                            if(chatMsgText2.height <= 25){
                                80
                            }
                            else{
                                chatMsgText2.height + 60
                            }
                        }
                        visible: model.self

                        Text { // 用户名
                            text: model.username
                            font.pixelSize: 16
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
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.right: parent.right
                            anchors.rightMargin: 15

                            Image {
                                width: 50
                                height: 50
                                source: model.avatar
                                mipmap: true // 抗锯齿
                            }
                        }

                        Rectangle{
                            width: chatMsgText2.width + 20
                            height: chatMsgText2.height + 20
                            radius: 8
                            color: "#4CFD01"
                            anchors.right: chatProfilePicSelf.left
                            anchors.rightMargin: 15
                            anchors.top: parent.top
                            anchors.topMargin: 30

                            FluCopyableText { // 消息
                                id: chatMsgText2
                                text: model.message
                                width: {
                                    if(chatMsgText2.width >= 380) {380}
                                }
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                font.pixelSize: 18
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }
    }

    property var emojis:
        ["😂", "🤣", "😅", "😀", "😊", "😭", "🫢", "😴", "🥱", "🤐", "😝", "😯",
        "😁", "😘", "🤗", "😫", "😍", "😒", "😎", "😉", "😢", "😩", "😡", "🥵",
        "🤭", "🙄", "🤨", "😮", "😨", "🤢", "💖", "💕", "🙌", "👍", "👌", "🤞"]

    FluMenu{
        id:emojiMenu
        width: 290

        ScrollView {
            width: parent.width
            height: 160

            GridLayout { // 网格布局
                columns: 6 // 指定列数
                width: parent.width
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 10

                Repeater {
                    model: 36

                    Rectangle {
                        height: 40
                        width: 40
                        FluButton{
                            id: emjBtn
                            text: emojis[index]
                            height: 40
                            width: 40
                            font.pixelSize: 30

                            onClicked: {
                                chatTextBox.text = chatTextBox.text + emjBtn.text
                                chatTextBox.cursorPosition = chatTextBox.text.length
                                emojiMenu.close()
                            }
                        }
                    }
                }
            }
        }
    }

    FluMenu{ // 语音消息菜单，功能有待实现
        id:voiceMsgMenu
        width: 150

        Item{
            width:parent.width
            height: 100

            Text {
                id: voiceMsgMenuText
                text: qsTr("正在录制...")
                font.pixelSize: 18
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                FluFilledButton{
                    id: voiceMsgMenuBtn
                    disabled: true
                    text: qsTr("试听")

                    onClicked: {
                        // 播放
                    }
                }

                FluFilledButton{
                    id: voiceMsgMenuBtn2
                    text: qsTr("完成")
                    onClicked: {
                        voiceMsgMenuText.text = "录制完成"
                        voiceMsgMenuBtn.disabled = false
                        voiceMsgMenuBtn2.text = "发送"
                    }
                }
            }
        }

        onClosed: {
            // 菜单关闭时

            voiceMsgMenuText.text = "正在录制..."
            voiceMsgMenuBtn.disabled = true
            voiceMsgMenuBtn2.text = "完成"
        }
    }

    FluMenu{ // 图片消息菜单，功能有待实现
        id:imgMsgMenu
        width: 100

        Item{
            width:parent.width
            height: 40

            FluFilledButton{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("选取图片")

                onClicked: {
                    // 发送图片的操作
                }
            }
        }
    }

    FluMenu{ // 文件消息菜单，功能有待实现
        id:fileMsgMenu
        width: 100

        Item{
            width:parent.width
            height: 40

            FluFilledButton{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("选取文件")

                onClicked: {
                    // 发送文件的操作
                }
            }
        }
    }

    FluArea {
        id: chatToolsArea
        width: parent.width
        height: 50
        anchors.top: chatMsgArea.bottom

        Row{
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5



            FluIconButton{
                iconSource:FluentIcons.EmojiTabSmilesAnimals
                anchors.verticalCenter: parent.verticalCenter

                onClicked: {
                    emojiMenu.popup();
                }
            }

            FluIconButton{
                iconSource:FluentIcons.MicrophoneListening
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    voiceMsgMenu.popup()
                }
            }

            FluIconButton{
                iconSource:FluentIcons.ImageExport
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    imgMsgMenu.popup()
                }
            }

            FluIconButton{
                iconSource:FluentIcons.Folder
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    fileMsgMenu.popup()
                }
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
                var mes = {"username":curuser.name, "avatar": curuser.avatar,
                    "message": chatTextBox.text, "self": true}
//                chatModel.append({"username": "大黄", "avatar": "images/test3.jpg",
//                                 "message": chatTextBox.text, "self": true})

                sendChatMessageSignal(curuser.id,model.contextid,model.isgroup,chatTextBox.text,QDateTime::currentDateTime().toTime_t());
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
