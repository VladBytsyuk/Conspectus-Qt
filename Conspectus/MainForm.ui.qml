import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 640
    height: 480
    property alias buttonAdd: buttonAdd

    property alias buttonView: buttonView

    RowLayout {
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        width: 310
        height: 50

        Button {
            id: buttonView
            width: 150
            height: 50
            text: "VIEW LECTURE"
            visible: true
        }

        Button {
            id: buttonAdd
            x: 160
            width: 150
            height: 50
            text: qsTr("ADD LIST")
            Layout.fillWidth: false
        }
    }

    Text {
        id: title
        x: 220
        y: 65
        text: qsTr("CONSPECTUS")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 32
    }
}
