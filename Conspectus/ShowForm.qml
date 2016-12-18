import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1

Item {
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int shadowOffset: 5
    property int boxWidth: 200
    property int boxHeight: 25
    property int verticalNotPressed: 16
    property int horizontalNotPressed: 135
    property int rOffShadowNotPressed: 8
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

    property alias buttonEdit: buttonEdit
    property alias buttonCancel: buttonCancel

        Button {
            id: buttonCancel
            width: buttonWidth
            height: buttonHeight
            text: "CANCEL"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonCancel.pressed ? horizontalNotPressed+addPressed : horizontalNotPressed
            anchors.bottom: parent.bottom
            anchors.bottomMargin: buttonCancel.pressed ? verticalNotPressed-addPressed : verticalNotPressed
            visible: true
            style: buttonStyle
        }

        Button {
            id: buttonEdit
            width: buttonWidth
            height: buttonHeight
            objectName: "buttonEdit"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonEdit.pressed ? -horizontalNotPressed+addPressed : -horizontalNotPressed
            anchors.bottom: parent.bottom
            anchors.bottomMargin: buttonEdit.pressed ? verticalNotPressed-addPressed : verticalNotPressed
            text:"SAVE"
            visible: true
            style: buttonStyle
        }

    DropShadow {
        anchors.fill: buttonCancel
        source: buttonCancel
        color: "#50000000"
        horizontalOffset: buttonCancel.pressed ? shadowOffset-addPressed : shadowOffset
        verticalOffset: buttonCancel.pressed ? shadowOffset-addPressed : shadowOffset
        radius: buttonCancel.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
        samples: 17
    }

    DropShadow {
        anchors.fill: buttonEdit
        source: buttonEdit
        color: "#50000000"
        horizontalOffset: buttonEdit.pressed ? shadowOffset-addPressed : shadowOffset
        verticalOffset: buttonEdit.pressed ? shadowOffset-addPressed : shadowOffset
        radius: buttonEdit.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
        samples: 17
    }


    /**
    * Top bar
    */
    Rectangle {
        id: topBar
        width: parent.width - 16
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        border.color: "#6988bd"
        color: "#006988bd"
        radius: 3

        Flow {
            id: flowTopBar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            width: 600
            height: 30
            spacing: 5

            Image {
                source: "/assets/garbage.png"
                width: 30
                fillMode: Image.PreserveAspectFit
            }
            Image {
                source: "/assets/printer.png"
                width: 30
                fillMode: Image.PreserveAspectFit
            }


       } //End Top bar
    }



    function showImage(path){
        mainImage.source = path;
    }



    Rectangle {
        anchors.top: topBar.bottom
        anchors.bottom: buttonCancel.top
        anchors.bottomMargin: 10
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        color: "#00000000"

        Image {
            id: mainImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
        }
    }

    function setSource(path) {
        mainImage.source = "image://sourceDir/" + path;
    }

}
