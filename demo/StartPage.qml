import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow {
    id:startPage
    visible: true
    width: 400
    height: 480
    title: qsTr("FutureChat")
    objectName: "startPage_object"

    // 登录信号
    property string userid: ""
    property string userpwd: ""
    signal loginSignal(string userid, string userpwd)

    // 注册信号
    property string regname: ""
    property string regpwd: ""
    property string regpwd2: ""
    signal regSignal(string regname, string regpwd)

    // Loader加载不同组件，实现切换页面的功能
    Loader{
        id:myLoader
        anchors.centerIn: parent // 弹出的界面都居中显示
    }
    Component.onCompleted: myLoader.sourceComponent = loginPage // 一开始显示登录页面

    // 2. 登录-Component
    Component{
        id:loginPage
        LoginPage {
            width: 400
            height: 480
            //anchors.centerIn: parent
        }


    }

    // 3.注册-Component
    Component{
        id:regPage
        RegisterPage {
            width: 400
            height: 560
            //anchors.centerIn: parent
        }
    }
}
