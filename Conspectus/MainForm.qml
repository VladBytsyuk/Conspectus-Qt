import QtQuick 2.5
import QtQuick.Controls 1.4
//import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int buttonWidth: 200
    property int buttonHeight: 100
    property int shadowOffset: 5
    property int verticalNotPressed: 20
    property int horizontalNotPressed: 135
    property int rOffShadowNotPressed: 12
    property int addPressed: 2

    Component {
        id: buttonStyle
        ButtonStyle {
            background: Rectangle{
                color: control.pressed ? "#697BBD"  : "#6988bd"
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
    
    property alias buttonAdd: buttonAdd
    property alias buttonView: buttonView

        Button {
            id: buttonView
            width: buttonWidth
            height: buttonHeight
            text: "VIEW LECTURE"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonView.pressed ? -horizontalNotPressed+addPressed : -horizontalNotPressed
            anchors.verticalCenterOffset: buttonView.pressed ? verticalNotPressed+addPressed : verticalNotPressed
            anchors.verticalCenter: parent.verticalCenter
            visible: true            
            style: buttonStyle
        }

        Button {
            id: buttonAdd
            width: buttonWidth
            height: buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonAdd.pressed ? horizontalNotPressed+addPressed : horizontalNotPressed
            anchors.verticalCenterOffset: buttonAdd.pressed ? verticalNotPressed+addPressed : verticalNotPressed
            anchors.verticalCenter: parent.verticalCenter
            text:"ADD LIST"
            visible: true
            style: buttonStyle
            }
    DropShadow {
        anchors.fill: buttonAdd
        source: buttonAdd
        color: "#50000000"
        horizontalOffset: buttonAdd.pressed ? shadowOffset-addPressed : shadowOffset
        verticalOffset: buttonAdd.pressed ? shadowOffset-addPressed : shadowOffset
        samples: 25//buttonAdd.hovered ? 25 : 45
        radius: buttonAdd.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
    }

    DropShadow {
        anchors.fill: buttonView
        source: buttonView
        color: "#50000000"
        horizontalOffset: buttonView.pressed ? shadowOffset-addPressed : shadowOffset
        verticalOffset: buttonView.pressed ? shadowOffset-addPressed : shadowOffset
        radius: buttonView.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
        samples: 25
    }


    Text {
        id: title
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -125
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
        font.bold: true
        color: "#263238"
    }
}
