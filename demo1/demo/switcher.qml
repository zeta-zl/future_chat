import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    // 1. Loader加载不同组件，实现切换页面的功能
    Loader{
        id:myLoader
        anchors.centerIn: parent // 弹出的界面都居中显示
    }
    Component.onCompleted: myLoader.sourceComponent = loginPage // 一开始显示登录页面

    // 2. 登录页面-Component
    Component{
        id:loginPage
        LoginPage{
            width: 300
            height: 200
            anchors.centerIn: parent
        }
    }

    // 3.注册界面-Component
    Component{
        id:regPage
        RegisterPage{
            width: 500
            height: 350
            //anchors.centerIn: parent
        }
    }
}
