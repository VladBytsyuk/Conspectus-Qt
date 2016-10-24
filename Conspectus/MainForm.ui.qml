import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int scrWidth: 640;
    property int scrHeight: 480;
    property int buttonWidth: 200;
    property int buttonHeight: 100;
    property int shadowOffset: 5

    width: scrWidth
    height: scrHeight

    Rectangle {
        anchors.fill: parent
        //color: "#fffdee"
        //color: "#0198a5"
        color: "#f6f6f6"
    }
    
    property alias buttonAdd: buttonAdd
    property alias buttonView: buttonView

        Button {
            id: buttonView
            width: buttonWidth
            height: buttonHeight
            text: "VIEW LECTURE"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -120
            anchors.verticalCenterOffset: 25
            anchors.verticalCenter: parent.verticalCenter
            visible: true            
            style: ButtonStyle {
                background: Rectangle{
                    color: "#6988bd"

//                    color: "#ff5a5b"
//                    border.color: "#0198a5"
//                    border.width: 1
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

        Button {
            id: buttonAdd
            width: buttonWidth
            height: buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 120
            anchors.verticalCenterOffset: 25
            anchors.verticalCenter: parent.verticalCenter
            text:"ADD LIST"
            visible: true
            style: ButtonStyle{
                background: Rectangle{
                    color: "#6988bd"
//                    color: "#fffdee"
//                    border.color: "#65cedb"
//                    border.width: 1
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
    DropShadow {
        anchors.fill: buttonAdd
        source: buttonAdd
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
    }

    DropShadow {
        anchors.fill: buttonView
        source: buttonView
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
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
