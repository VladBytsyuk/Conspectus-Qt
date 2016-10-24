import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

Item {
    property int scrWidth: 640;
    property int scrHeight: 480;
    property int buttonWidth: 200;
    property int buttonHeight: 100;

    width: scrWidth
    height: scrHeight

    Rectangle {
 //       x: 0
 //       y: 0
 //       width: scrWidth
 //       height: scrHeight
        anchors.fill: parent
        color: "#C5CAE9"
        //color: "#faebd7"
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
                    color: "#80D8FF"
                    border.color: black
                    border.width: 1
                    radius: 5
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
                    color: "#80D8FF"
                    border.color: black
                    border.width: 1
                    radius: 5
                }
            }

        }


    Text {
        id: title
        x: 220
        y: 65
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -125
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
    }
}
