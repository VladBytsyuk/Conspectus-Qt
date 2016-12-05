import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int shadowOffset: 5
    property int boxWidth: 200
    property int boxHeight: 25


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

//    Rectangle {
//        anchors.fill: parent
//        color: "#f6f6f6"

//        TextField {
//            id: textField1
//            width: boxWidth
//            height: boxHeight
//            placeholderText: qsTr("Text Field")
//            inputMethodHints: Qt.ImhNoAutoUppercase
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenterOffset: -70
//            anchors.verticalCenter: parent.verticalCenter
//        }
//    }

//    Button {
//        id: buttonBrowse
//        width: 70
//        height: boxHeight
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.horizontalCenterOffset: 150
//        anchors.verticalCenterOffset: -70
//        anchors.verticalCenter: parent.verticalCenter
//        text:"Browse"
//        visible: true
//        style:  ButtonStyle {
//            background: Rectangle{
//                color: "#f0c150"
//                radius: 3
//            }
//            label: Text {
//                renderType: Text.NativeRendering
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                font.family: "Helvetica"
//                //font.pointSize: 8
//                font.bold: true
//                color: "black"
//                text: control.text
//            }
//        }
//    }

//    DropShadow {
//        anchors.fill: buttonBrowse
//        source: buttonBrowse
//        color: "#50000000"
//        horizontalOffset: 3
//        verticalOffset: 3
//        radius: 8
//        samples: 17
//    }
    
    property alias buttonOk: buttonOk
    property alias buttonCancel: buttonCancel

        Button {
            id: buttonCancel
            width: buttonWidth
            height: buttonHeight
            text: "CANCEL"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 120
            anchors.verticalCenterOffset: 180
            anchors.verticalCenter: parent.verticalCenter
            visible: true            
            style: buttonStyle
        }

        Button {
            id: buttonOk
            width: buttonWidth
            height: buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -120
            anchors.verticalCenterOffset: 180
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
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -160
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
        font.bold: true
    }

    Grid {
        id: grid1
//        x: 19
//        y: 121
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 599
        height: 259
//        columns:3
        spacing:2
        Rectangle { color: "red"; width: 599; height: 259 }
//        Rectangle { color: "green"; width: 120; height: 50 }
//        Rectangle { color: "blue"; width: 215; height: 80 }
//        Rectangle { color: "yellow"; width: 50; height: 50 }
//        Rectangle { color: "black"; width: 410; height: 10 }
    }


}
