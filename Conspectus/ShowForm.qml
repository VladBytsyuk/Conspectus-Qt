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

    property string current_image_name: ""
    signal turnedLeft(string name)
    signal turnedRight(string name)
    signal printed(string name)
    signal greyscaled(string name)
    signal deleted(string name)
    signal updateViewForm()

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

    function showViewForm() {
        updateViewForm();
        viewForm.showViewForm();
    }


    Flow {
        id: flowButtonLeft
        width: 25
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 5

    }
    Rectangle {
        id: buttonLeft
        objectName: "buttonLeft"
        width: flowButtonLeft.width
        height: flowButtonLeft.height
        anchors.horizontalCenter: flowButtonLeft.horizontalCenter
        anchors.verticalCenter: flowButtonLeft.verticalCenter
        radius: 3
        color: buttonLeftMA.containsMouse ? (buttonLeftMA.pressed ? "#40000000" : "#20000000") : "#00000000"
        visible: buttonLeft.isExistsLeft ? true : false

        property bool isExistsLeft: true

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: parent.width
            source: "/assets/arrow_left.png"
            visible: parent.visible
        }

        MouseArea {
            id: buttonLeftMA
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                viewForm.setPreviousImage()
            }
        }

    }


    Flow {
        id: flowButtonRight
        width: 25
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 5
    }
    Rectangle {
        id: buttonRight
        objectName: "buttonRight"
        width: flowButtonRight.width
        height: flowButtonRight.height
        anchors.horizontalCenter: flowButtonRight.horizontalCenter
        anchors.verticalCenter: flowButtonRight.verticalCenter
        radius: 3
        color: buttonRightMA.containsMouse ? (buttonRightMA.pressed ? "#40000000" : "#20000000") : "#00000000"
        visible: buttonRight.isExistsRight ? true : false

        property bool isExistsRight: true

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: parent.width
            source: "/assets/arrow_right.png"
            visible: parent.visible
        }

        MouseArea {
            id: buttonRightMA
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                viewForm.setNextImage()
            }
        }

    }


    /**
    * Top bar
    */
    Rectangle {
        id: topBar
        width: parent.width - 16
        height: 60
        anchors.left: flowButtonLeft.right
        anchors.right: flowButtonRight.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        //anchors.horizontalCenter: parent.horizontalCenter
        border.color: "#6988bd"
        color: "#006988bd"
        radius: 3


        Flow {
            id: flowTopBar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20

            ToolButton{
                id: toolButtonPrinter
                height: parent.height

                Image {
                    source: "/assets/printer.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: showForm.printed(current_image_name)
            }
            ToolButton{
                id: toolButtonTurnLeft
                height: 30
                Image {
                    source: "/assets/refresh.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: showForm.turnedLeft(current_image_name)
            }
            ToolButton{
                id: toolButtonTurnRight
                height: 30
                Image {
                    source: "/assets/refresh.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: showForm.turnedRight(current_image_name)
            }
            ToolButton{
                id: toolButtonZoom
                height: 30
                Image {
                    source: "/assets/zoom.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            ToolButton{
                id: toolButtonZoomOut
                height: 30
                Image {
                    source: "/assets/zoom-out.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
            ToolButton{
                id: toolButtonMoon
                height: 30
                Image {
                    source: "/assets/moon.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: showForm.greyscaled(current_image_name)
            }
            ToolButton{
                id: toolButtonGarbage
                height: 30
                Image {
                    source: "/assets/garbage.png"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: showForm.deleted(current_image_name)
            }
       } //End Top bar
    }


    /**
    * Main image
    */
    Rectangle {
        anchors.top: topBar.bottom
        anchors.bottom: flowEditCancel.top
        anchors.bottomMargin: 10
        anchors.topMargin: 5
        anchors.left: flowButtonLeft.right
        anchors.right: flowButtonRight.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        color: "#00000000"

        Image {
            id: mainImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
        }
    }

    Flow {
        id: flowEditCancel
        width: parent.width
        height: buttonHeight + 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter

    }

    function setSource(path, isExistsLeft, isExistsRight) {
        buttonLeft.isExistsLeft = isExistsLeft;
        buttonRight.isExistsRight = isExistsRight;

        mainImage.source = "image://sourceDir/" + path;
        current_image_name = path;
    }

    function reloadImage() {
        mainImage.source = "";
        mainImage.source = "image://sourceDir/" + current_image_name;
    }
}
