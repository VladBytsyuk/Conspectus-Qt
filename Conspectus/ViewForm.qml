import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int buttonWidth: 200;
    property int buttonHeight: 50;
    property int shadowOffset: 5

    Component {
        id: buttonStyle
        ButtonStyle {

            background: Rectangle{
                color: "#6988bd"
                radius: 3
            }
            label: Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                font.pointSize: 12
                font.bold: true
                color: "white"
                text: control.text
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#f6f6f6"
    }
    
    property alias buttonOk: buttonOk
    property alias buttonCancel: buttonCancel

        Button {
            id: buttonCancel
            width: buttonWidth
            height: buttonHeight
            text: "CANCEL"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -120
            anchors.verticalCenterOffset: 150
            anchors.verticalCenter: parent.verticalCenter
            visible: true            
            style: buttonStyle
        }

        Button {
            id: buttonOk
            width: buttonWidth
            height: buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 120
            anchors.verticalCenterOffset: 150
            anchors.verticalCenter: parent.verticalCenter
            text:"OK"
            visible: true
            style: buttonStyle
        }

    DropShadow {
        anchors.fill: buttonCancel
        source: buttonCancel
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
        radius: 8
        samples: 17
    }

    DropShadow {
        anchors.fill: buttonOk
        source: buttonOk
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
        radius: 8
        samples: 17
    }


    Text {
        id: title
//        x: 220
//        y: 65
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -125
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
        font.bold: true
    }

//    DropShadow {
//        anchors.fill: title
//        source: title
//        color: "#20000000"
//        horizontalOffset: shadowOffset
//        verticalOffset: shadowOffset
//    }
}
