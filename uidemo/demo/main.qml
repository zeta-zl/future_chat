import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import FluentUI 1.0

FluWindow {
    visible: true
    width: 1280
    height: 800
    title: qsTr("FutureChat")

    ListModel {
        id: friendModel

    }
}
