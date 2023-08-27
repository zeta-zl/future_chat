import QtQuick 2.12
import QtQuick.Controls 2.12
import FluentUI 1.0
import "ColorPicker"

Item {
    property alias colorValue: color_picker.colorValue
    width: color_picker.width+10
    height: color_picker.height
    FluArea{
        anchors.fill: parent
        radius: 5
        FluShadow{
            radius: 5
        }
        ColorPicker{
            id:color_picker
        }
    }
    function setColor(color) {
        color_picker.setColor(color)
    }
}

