import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0
import QtGraphicalEffects 1.0

FluWindow {
    id: add
    width: 400
    height: 200
    visible: true
    title: qsTr("添加好友")
    objectName: "addPage_object"

    // 搜索陌生人
    property string strangerId: ""
    signal searchStanger(string strangerId,string curid)

    Item{
        id:r
        width: 300
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        FluTextBox{
            width: 230
            id:text_box
            placeholderText: "请输入id"
            anchors{
                topMargin: 40
                top:parent.top
                left: parent.left
            }
        }
        FluFilledButton{
            text:"搜索"
            anchors{
                left: text_box.right
                verticalCenter: text_box.verticalCenter
                leftMargin: 14
            }
            onClicked: {
                add.height = 250
                searchResult.visible = true
                strangerId=text_box.text
                searchStanger(strangerId,curuser.id)
            }
        }

    }
    Item
    {
        id:searchResult
        visible: false
        width: r.width
        height: r.height
        anchors.top: r.bottom
        anchors.horizontalCenter: r.horizontalCenter
//        anchors.left: parent.left
//        anchors.leftMargin: 18
//        anchors.right: parent.right
//        anchors.rightMargin: 18

            Text {
                id: pInf
                text: qsTr("<font color='#767777'>联系人</font>")
                //visible: isPerson
            }

//            Text {
//                id: gInf
//                anchors.top: pInfList.bottom
//                anchors.topMargin: 0
//                text: qsTr("<font color='#767777'>群组</font>")
//                visible: !isPerson
//            }
            FluArea
            {
                id: pInfList
                anchors.top: pInf.bottom
                width: parent.width
                height: parent.height
                FluFilledButton{
                    text: "添加"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 15
                }
                Rectangle{
                    id: img
                    width: 70
                    height: 70
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 15
                    Image {
                        width: parent.width
                        height: parent.height
                        source: "images/test2.png"
                    }
                    layer.enabled : true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        color: "black"
                        samples: 8
                    }
                }
                Text {
                    id: searchName
                    text: qsTr("苏打") + qsTr("<font color=\"#54b4ef\">(") + qsTr("10001") + qsTr(")</font>")
                    anchors.left: img.right
                    anchors.verticalCenter: img.verticalCenter
                    font.pixelSize: 16
                    anchors.leftMargin: 14
                }

            }
    }
}
