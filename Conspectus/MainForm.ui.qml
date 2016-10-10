import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

Item {
    property int scrWidth: 640;
    property int scrHeight: 480;

    width: scrWidth
    height: scrHeight

    Rectangle {
        x: 0
        y: 0
        width: scrWidth
        height: scrHeight
        color: "#C5CAE9"
        //color: "#faebd7"
    }
    
    property alias buttonAdd: buttonAdd
    property alias buttonView: buttonView

/*    RowLayout {
        width: 310
        height: 100
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent        */

        Button {
            id: buttonView
            x: 150
            y: 155
            width: 150
            height: 50
            text: "VIEW LECTURE"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: -1
            isDefault: true
            visible: true            
            style: ButtonStyle {
                background: Rectangle{
                    color: "#80D8FF"
                    border.color: black
                    border.width: 3
                    radius: 5
                }
            }
        }

        Button {
            id: buttonAdd
            x: 320
            y: 155
            width: 150
            height: 50
            text:"ADD LIST"
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            visible: true
            style: ButtonStyle{
                background: Rectangle{
                    color: "#80D8FF"
                    border.color: black
                    border.width: 3
                    radius: 5
                }
            }
        }


    Text {
        id: title
        x: 220
        y: 65
        text: "CONSPECTUS"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 32
    }
}
