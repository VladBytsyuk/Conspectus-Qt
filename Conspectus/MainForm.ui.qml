import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 640
    height: 480
    
    property alias buttonAdd: buttonAdd
    property alias buttonView: buttonView

    RowLayout {
        width: 310
        height: 100
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent

        Button {
            id: buttonView
            y: 25
            width: 150
            height: 50
            text: "VIEW LECTURE"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: -1
            isDefault: true
            visible: true
        }

        Button {
            id: buttonAdd
            x: 160
            y: 25
            width: 150
            height: 50
            text:"ADD LIST"
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            visible: true
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
