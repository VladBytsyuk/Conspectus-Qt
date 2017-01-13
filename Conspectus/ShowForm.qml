import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import QtQml.Models 2.2

Item {
    id: rootShow
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int shadowOffset: 5
    property int boxWidth: 200
    property int boxHeight: 25
    property int verticalNotPressed: 16
    property int horizontalNotPressed: 135
    property int rOffShadowNotPressed: 8
    property int addPressed: 2
    property int iconSize: 30
    property int topBarSpacing: 15
    property int panelWidth: 160

    property alias buttonCancel: buttonCancel

    property string current_image_name: ""
    signal turnedLeft(string name)
    signal turnedRight(string name)
    signal printed(string name)
    signal greyscaled(string name)
    signal deleted(string name)
    signal updateViewForm()
    signal imageSet(string name)

    function clearTagsComments() {
        tagField.text = "";
        commentField.text = "";
    }

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

    Button {
        id: buttonCancel
        width: buttonWidth
        height: buttonHeight
        text: "CANCEL"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: buttonCancel.pressed ? addPressed : 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: buttonCancel.pressed ? verticalNotPressed-addPressed : verticalNotPressed
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
            onClicked: viewForm.setPreviousImage()
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
            onClicked: viewForm.setNextImage()
        }
    }


    /*      Top bar     */
    Rectangle {
        id: topBar
        height: 60
        anchors.left: flowButtonLeft.right
        anchors.right: flowButtonRight.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        //anchors.horizontalCenter: parent.horizontalCenter
        border.color: "#6988bd"
        color: "#006988bd"
        radius: 3

        Item {
            id: flowTopBar
            width: 7 * (iconSize + topBarSpacing) + zoomInSlider.width
            height: iconSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            Row {
                spacing: topBarSpacing

                ToolButton{
                    id: toolButtonPrinter
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/printer.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit

                    }
                    onClicked: showForm.printed(current_image_name)
                }
                ToolButton{
                    id: toolButtonTurnLeft
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/left.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                        antialiasing: true
                    }
                    onClicked: showForm.turnedLeft(current_image_name)
                }

                Image {
                    source: "/assets/zoom-out.png"
                    height: iconSize
                    width: iconSize
                    fillMode: Image.PreserveAspectFit
                }
                Slider {
                    id: zoomInSlider
                    height: iconSize
                    orientation: Qt.Horizontal
                    visible: true
                    minimumValue: 0
                    maximumValue: 100
                    value: 0

                    onValueChanged: {
                        mainImage.height = mainImageContainer.height + 50 * zoomInSlider.value;
                        mainImage.width = mainImageContainer.width + 50 * zoomInSlider.value;

                        scroll.flickableItem.contentY = scroll.flickableItem.contentHeight / 2 - scroll.height / 2;
                        scroll.flickableItem.contentX = scroll.flickableItem.contentWidth / 2 - scroll.width / 2;
                        //scroll.flickableItem.contentX = mouse.X - scroll.width / 2;
                        //scroll.flickableItem.contentY = mouse.Y - scroll.height / 2;
                    }
                }
                Image {
                    source: "/assets/zoom.png"
                    height: iconSize
                    width: iconSize
                    fillMode: Image.PreserveAspectFit
                }

                ToolButton{
                    id: toolButtonTurnRight
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/right.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: showForm.turnedRight(current_image_name)
                }
                ToolButton{
                    id: toolButtonMoon
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/moon.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: showForm.greyscaled(current_image_name)
                }
                ToolButton{
                    id: toolButtonGarbage
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/garbage.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: showForm.deleted(current_image_name)
                }


                ToolButton {
                    id: showPanel
                    property bool isOpen: false
                    width: iconSize
                    height: iconSize

                    ColorOverlay {
                        anchors.fill: parent
                        color: "#f0c150"
                    }

                    onClicked: {
                         panel.state = !isOpen ? "open" : "";
                         isOpen = !isOpen;
                    }
                }
           } //End top flow
       }
    }

    /*      Main image      */
    Rectangle {
        id: mainImageContainer
        anchors.top: topBar.bottom
        anchors.bottom: flowEditCancel.top
        anchors.bottomMargin: 10
        anchors.topMargin: 5
        anchors.left: flowButtonLeft.right
        anchors.right: flowButtonRight.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        color: "#00000000"
        onHeightChanged: setNaturalSize()

        ScrollView {
            id: scroll
            width: mainImageContainer.width
            height: mainImageContainer.height
            verticalScrollBarPolicy : Qt.ScrollBarAlwaysOff
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            flickableItem.interactive: true
            focus: true

            Image {
                id: mainImage
                width: mainImageContainer.width
                height: mainImageContainer.height
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                source: ""
                cache: false
            }
        }

        /*      Image loading indicator     */
        Item {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            implicitWidth: 64
            implicitHeight: 64

            Item {
                id: item
                x: parent.width / 2 - 32
                y: parent.height / 2 - 32
                width: 64
                height: 64
                opacity: (mainImage.status === Image.Loading) ? 1 : 0

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 250
                    }
                }

                RotationAnimator {
                    target: item
                    running: mainImage.status === Image.Loading
                    from: 0
                    to: 360
                    loops: Animation.Infinite
                    duration: 1250
                }

                Repeater {
                    id: repeater
                    model: 6

                    Rectangle {
                        x: item.width / 2 - width / 2
                        y: item.height / 2 - height / 2
                        implicitWidth: 10
                        implicitHeight: 10
                        radius: 5
                        color: "#6988bd"
                        transform: [
                            Translate {
                                y: -Math.min(item.width, item.height) * 0.5 + 5
                            },
                            Rotation {
                                angle: index / repeater.count * 360
                                origin.x: 5
                                origin.y: 5
                            }
                        ]
                    }
                }
            }
        }   //End image loading indicator
    }   // End Main Image

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
        setNaturalSize();

        rootShow.imageSet(current_image_name);
    }

    function reloadImage() {
        mainImage.source = "";
        mainImage.source = "image://sourceDir/" + current_image_name;
        setNaturalSize();

        rootShow.imageSet(current_image_name);
    }

    function setNaturalSize() {
        zoomInSlider.value = 0;
        mainImage.height = mainImageContainer.height;
        mainImage.width = mainImageContainer.width;
    }






    Item {
        id: panel
        width: panelWidth - 25
        height: rootShow.height
        anchors.left: rootShow.right

        Text {
            id: tagTitle
            height: 20
            width: parent.width
            anchors.top: parent.top
            text: "Tags:"
            font.pointSize: 12
        }

        TextField {
            id: tagField
            objectName: "tagField"
            width: parent.width
            height: 100
            anchors.top: tagTitle.bottom

            signal tagChanged(string file_name, string new_tag)
        }

        Text {
            id: commentTitle
            height: 20
            width: parent.width
            anchors.top: tagField.bottom
            text: "Commentaries:"
            font.pointSize: 12
        }

        TextField {
            id: commentField
            objectName: "commentField"
            width: parent.width
            height: 210
            anchors.top: commentTitle.bottom

            signal commentChanged(string file_name, string new_comment)
        }

        Button {
            id: saveTagsComments
            objectName: "saveTagsComments"
            width: parent.width
            height: 25
            anchors.top: commentField.bottom
            anchors.topMargin: 15

            text: "Save"

            onClicked: {
                tagField.tagChanged(current_image_name, tagField.text);
                commentField.commentChanged(current_image_name, commentField.text);
            }
        }

//        Column {
//            id: boxesColumn
//            width: parent.width
//            height: parent.height - tagTitle.height - tagField.height - commentTitle.height - commentField.height
//            anchors.top: commentField.bottom
//            anchors.topMargin: 30

//            spacing: 20

        ComboBox {
            id: boxTerm
            width: parent.width
            height: boxHeight

            anchors.top: saveTagsComments.bottom
            anchors.topMargin: 30

            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "boxTerm"
            Component.onCompleted: {
                currentIndex = -1
            }
//________________________________________________________________________________
//                states: State {
//                    name: "highlight"
//                    PropertyChanges {target: dropShadowTerm; color: "#9f0000";
//                                     horizontalOffset: 0; verticalOffset: 0;}
//                }

//                editable: true
//                //onCurrentTextChanged: boxTerm.termSelect(model[currentIndex])
//                onEditTextChanged: boxTerm.termSelect(boxTerm.editText.toString())

//__________________________________________________________________________________
            signal termSelect(string term)
            onCurrentTextChanged: boxTerm.termSelect(model[currentIndex])

            inputMethodHints: Qt.ImhNoAutoUppercase
            style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#f0c150"
                }
                label: Text {
                    renderType: Text.NativeRendering
                    font.bold: true
                    color: "black"
                    text: control.currentIndex===-1?"Term":control.currentText
                }
            }
        }

        ComboBox {
            id: boxSubject
            width: parent.width
            height: boxHeight

            anchors.top: boxTerm.bottom
            anchors.topMargin: 25

            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "boxSubject"
            Component.onCompleted: currentIndex = -1

            signal subjectSelect(string subject)
            onCurrentTextChanged: boxSubject.subjectSelect(model[currentIndex])

            style: ComboBoxStyle {
                    background: Rectangle {
                        radius: 3
                        color: "#f0c150"
                    }
                    label: Text {
                        renderType: Text.NativeRendering
                        font.bold: true
                        color: "black"
                        text: control.currentIndex===-1?"Subject":control.currentText
                    }
            }
        }

        ComboBox {
            id: boxTheme
            width: parent.width
            height: boxHeight

            anchors.top: boxSubject.bottom
            anchors.topMargin: 25

            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "boxTheme"
            Component.onCompleted: currentIndex = -1

            signal themeSelect(string theme)
            onCurrentTextChanged: boxTheme.themeSelect(model[currentIndex])

            style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#f0c150"
                }
                label: Text {
                    renderType: Text.NativeRendering
                    color: "black"
                    font.bold: true
                    text:
                        control.currentIndex===-1?"Theme":control.currentText
                }
            }
        }

        Button {
            id: saveList
            width: parent.width * 3 / 4
            height: 25
            objectName: "buttonSave"
            text:"ADD"
            style:  ButtonStyle {
                background: Rectangle{
                    color: control.pressed ? "#f0b050"  : "#f0c150"
                    radius: 3
                }
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    color: "black"
                    text: control.text
                }
            }

            signal addList(string file_name)
            onClicked: saveList.addList(current_image_name)

//                anchors.top: boxTheme.bottom
//                anchors.topMargin: 25
            anchors.bottom: parent.bottom
            anchors.bottomMargin: saveList.pressed ? verticalNotPressed-addPressed : verticalNotPressed
            anchors.horizontalCenter: parent.horizontalCenter
        }
//        }
        DropShadow {
            anchors.fill: saveList
            source: saveList
            color: "#50000000"
            horizontalOffset: saveList.pressed ? shadowOffset-addPressed : shadowOffset
            verticalOffset: saveList.pressed ? shadowOffset-addPressed : shadowOffset
            radius: saveList.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
            samples: 17
        }

        DropShadow {
            id: dropShadowTerm
            anchors.fill: boxTerm
            source: boxTerm
            color: "#50000000"
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            samples: 17
        }
        DropShadow {
            id: dropShadowSubject
            anchors.fill: boxSubject
            source: boxSubject
            color: "#50000000"
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            samples: 17
        }
        DropShadow {
            id: dropShadowTheme
            anchors.fill: boxTheme
            source: boxTheme
            color: "#50000000"
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            samples: 17
        }

        states: [
            State {
                name: "open"
                PropertyChanges { target: rootShow; anchors.rightMargin: panelWidth; topBarSpacing: 5;
                    iconSize: rootShow.width > 766 ? iconSize : (5 * rootShow.width + 460) / 143 }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    duration: 200;
                    properties: "anchors.rightMargin,topBarSpacing,iconSize"
                }
            }
        ]
    }
}
