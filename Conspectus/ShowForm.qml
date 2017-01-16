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
    property int textSize: 10
    property string textColor: "#263238"
    property bool isCropActive: false
    property bool isNeedToCrop: false

    property alias buttonCancel: buttonCancel

    property string current_image_name: ""
    property string current_source_form: ""

    signal turnedLeft(int index, string name)
    signal turnedRight(int index, string name)
    signal printed(string name)
    signal improved(int index, string name)
    signal deleted(string name)
    signal updateViewForm()
    signal imageSet(int index, string form_name, string name)
    signal cropImage(int index, string name, int fromX, int fromY, int toX, int toY);

    //forced emit subjectSelect signal
    function emitTermSelect(term) {
        boxTerm.termSelect(term);
    }

    //forced emit subjectSelect signal
    function emitSubjectSelect(subject) {
        boxSubject.subjectSelect(subject);
    }

    //forced emit themeSelect signal
    function emitThemeSelect(theme) {
        boxTheme.themeSelect(theme);
    }


    function clearTagsComments() {
        tagField.text = "";
        commentField.text = "";
    }

    function clearCrop() {
        isCropActive = false;
        mainImage.opacity = 1;
        zoomInSlider.enabled = true;
        canvas.firstX = 0;
        canvas.firstY = 0;
        canvas.lastX = 0;
        canvas.lastY = 0;
        canvas.requestPaint();
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
                font.pointSize: textSize + 2
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
        if (current_source_form === "ViewForm") {
            updateViewForm();
            viewForm.showViewForm();
        } else if (current_source_form === "TagForm") {
            tagForm.showTagForm();
        }
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
            onClicked:  {
                if (current_source_form === "ViewForm") {
                    viewForm.setPreviousImage();
                } else if (current_source_form === "TagForm") {
                    tagForm.setPreviousImage();
                }
                clearCrop()
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
                if (current_source_form === "ViewForm") {
                    viewForm.setNextImage();
                } else if (current_source_form === "TagForm") {
                    tagForm.setNextImage();
                }
                clearCrop()
            }
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
        //border.color: "#6988bd"
        color: "#006988bd"
        radius: 3

        Item {
            id: flowTopBar
            width: 8 * (iconSize + topBarSpacing) + zoomInSlider.width
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
                    onClicked: showForm.turnedLeft(viewForm.getCurrentIndex(), current_image_name)
                }

                ToolButton{
                    id: zoomMinus
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/zoom-out.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: zoomInSlider.value = Math.max(0, zoomInSlider.value - 10);
                }

                Slider {
                    id: zoomInSlider
                    height: iconSize
                    width: 3 * iconSize + 2 * topBarSpacing
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
                    }
                }

                ToolButton{
                    id: zoomPlus
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/zoom.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: zoomInSlider.value = Math.min(100, zoomInSlider.value + 10);
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
                    onClicked: showForm.turnedRight(viewForm.getCurrentIndex(), current_image_name)
                }
                ToolButton{
                    id: toolButtonCrop
                    height: iconSize
                    width: iconSize
                    Image {
                        source: "/assets/cut.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: {
                        if (zoomInSlider.value != 0) return;
                        isCropActive = !isCropActive
                        mainImage.opacity = isCropActive ? 0.78 : 1
                        zoomInSlider.enabled = !isCropActive
                        if (isNeedToCrop) {
                            cropImage(viewForm.getCurrentIndex(), current_image_name,
                                      canvas.firstX * mainImage.sourceSize.width / canvas.width,
                                      canvas.firstY * mainImage.sourceSize.height / canvas.height,
                                      canvas.lastX * mainImage.sourceSize.width / canvas.width,
                                      canvas.lastY * mainImage.sourceSize.height / canvas.height);
                            canvas.firstX = 0;
                            canvas.firstY = 0;
                            canvas.lastX = 0;
                            canvas.lastY = 0;
                        }
                        canvas.requestPaint()
                    }
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
                    onClicked: showForm.improved(viewForm.getCurrentIndex(), current_image_name)
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


                Button {
                    id: showPanel
                    property bool isOpen: false
                    width: iconSize + 10
                    height: iconSize + 10
                    anchors.top: parent.top
                    anchors.topMargin: showPanel.pressed ? shadowOffset-2*addPressed : 0
                    style: ButtonStyle {
                        background: Rectangle {
                            color: "#00000000"
                        }
                    }

                    Rectangle {
                        id: showPanelBackground
                        width: iconSize
                        height: iconSize
                        color: "#f0c150"
                        radius: iconSize / 2

                        Image {
                            id: openPanel
                            source: "/assets/add.png"
                            anchors.fill: parent
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                    onClicked: {
                         panel.state = !isOpen ? "open" : "";
                         isOpen = !isOpen;
                    }
                    DropShadow {
                        id: dropShadowOpenPanel
                        anchors.fill: showPanelBackground
                        source: showPanelBackground
                        color: "#50000000"
                        horizontalOffset: showPanel.pressed ? shadowOffset-2*addPressed : shadowOffset-addPressed
                        verticalOffset: showPanel.pressed ? shadowOffset-2*addPressed : shadowOffset-addPressed
                        radius: showPanel.hovered ? rOffShadowNotPressed+8-4 : rOffShadowNotPressed
                        samples: 17
                    }
                }
           } //End top row
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

                Canvas {
                    id: canvas

                    width: mainImage.paintedWidth
                    height: mainImage.paintedHeight
                    anchors.horizontalCenter: mainImage.horizontalCenter
                    anchors.verticalCenter: mainImage.verticalCenter

                    property int firstX: 0
                    property int firstY: 0
                    property int lastX: 0
                    property int lastY: 0
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0,0,canvas.width,canvas.height)
                        if (isCropActive) {
                            ctx.lineWidth = 2
                            ctx.strokeStyle = "#af0000"
                            ctx.beginPath()
                            ctx.rect(firstX,firstY,lastX - firstX,lastY - firstY)
                            ctx.stroke()
                        }
                    }
                }

                MouseArea {
                    width: mainImage.paintedWidth
                    height: mainImage.paintedHeight

                    anchors.horizontalCenter: mainImage.horizontalCenter
                    anchors.verticalCenter: mainImage.verticalCenter

                    id: mouseArea_image
                    onPressed: {
                        if (!isCropActive) return;
                      //  appWindow.click = false
                        canvas.firstX = mouseX
                        canvas.firstY = mouseY
                    }
                    onPositionChanged: {
                        if (!isCropActive) return;
                        canvas.lastX = mouseX
                        canvas.lastY = mouseY
                        canvas.requestPaint()
                    }
                    onReleased: {
                        if (!isCropActive) return;
                        isNeedToCrop = true
                        canvas.lastX = (mouseX > mainImage.paintedWidth) ? mainImage.paintedWidth : mouseX
                        canvas.lastY = (mouseY > mainImage.paintedHeight) ? mainImage.paintedHeight : mouseY
                        canvas.lastX = (canvas.lastX < 0) ? 0 : canvas.lastX
                        canvas.lastY = (canvas.lastY < 0) ? 0 : canvas.lastY
                        if (canvas.lastX < canvas.firstX) {
                            var posX = canvas.lastX
                            canvas.lastX = canvas.firstX
                            canvas.firstX = posX
                        }
                        if (canvas.lastY < canvas.firstY) {
                            var posY = canvas.lastY
                            canvas.lastY = canvas.firstY
                            canvas.firstY = posY
                        }
                        canvas.requestPaint()
                    }
                    onClicked: {
                        if (!isCropActive) return;
                        if (mouse.button === Qt.RightButton) {
                           // appWindow.click = true
                            canvas.requestPaint()
                        }
                    }
                }
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

        if (current_source_form === "ViewForm") {
            rootShow.imageSet(viewForm.getCurrentIndex(), "ViewForm", current_image_name);
        } else if (current_source_form === "TagForm") {
            rootShow.imageSet(tagForm.getCurrentIndex(), "TagForm", current_image_name);
        }
    }

    function reloadImage() {
        mainImage.source = "";
        mainImage.source = "image://sourceDir/" + current_image_name;
        setNaturalSize();

        rootShow.imageSet(viewForm.getCurrentIndex(), current_image_name);
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
            anchors.topMargin: 17
            text: "Tags:"
            font.pointSize: textSize
            color: textColor
        }

        TextArea {
            id: tagField
            objectName: "tagField"
            width: parent.width
            height: 80
            anchors.top: tagTitle.bottom
            wrapMode: Text.WrapAnywhere
            signal tagChanged(string file_name, string new_tag)
        }

        Text {
            id: commentTitle
            height: 20
            width: parent.width
            anchors.top: tagField.bottom
            text: "Comments:"
            font.pointSize: textSize
            color: textColor
        }

        TextArea {
            id: commentField
            objectName: "commentField"
            width: parent.width
            height: 180
            anchors.top: commentTitle.bottom
            wrapMode: Text.WrapAnywhere
            signal commentChanged(string file_name, string new_comment)
        }

        Button {
            id: saveTagsComments
            objectName: "saveTagsComments"
            width: parent.width * 3 / 4
            height: 25
            anchors.top: commentField.bottom
            anchors.topMargin: saveTagsComments.pressed ? verticalNotPressed : verticalNotPressed-addPressed
            anchors.horizontalCenter: parent.horizontalCenter

            text: "SAVE"
            style:  ButtonStyle {
                background: Rectangle{
                    //color: control.pressed ? "#f0b050"  : "#f0c150"
                    color: control.pressed ? "#697BBD"  : "#6988bd"
                    //color: control.pressed ? "#af0000" :"#889f0000"
                    radius: 3
                }
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pointSize: textSize - 1
                    color: "white"
                    text: control.text
                }
            }

            onClicked: {
                tagField.tagChanged(current_image_name, tagField.text);
                commentField.commentChanged(current_image_name, commentField.text);
            }
        }
        DropShadow {
            anchors.fill: saveTagsComments
            source: saveTagsComments
            color: "#50000000"
            horizontalOffset: saveTagsComments.pressed ? shadowOffset-addPressed : shadowOffset
            verticalOffset: saveTagsComments.pressed ? shadowOffset-addPressed : shadowOffset
            radius: saveTagsComments.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
            samples: 17
        }

        Text {
            id: addText
            anchors.bottom: boxTerm.top
            anchors.bottomMargin: 20
            color: textColor
            text: " Add this list to another\npart of the conspect:"
            font.pointSize: textSize
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
        }

        ComboBox {
            id: boxTerm
            width: parent.width
            height: boxHeight

            anchors.bottom: boxSubject.top
            anchors.bottomMargin: 20

            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "boxTerm"
            Component.onCompleted: currentIndex = -1

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
                    color: textColor
                    text: control.currentIndex===-1?
                              "Term":
                              control.currentText.length>15?
                                  control.currentText.substring(0,12)+"...":
                                  control.currentText
                }
            }
        }

        ComboBox {
            id: boxSubject
            width: parent.width
            height: boxHeight

            anchors.bottom: boxTheme.top
            anchors.bottomMargin: 20

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
                        color: textColor
                        text: control.currentIndex===-1?
                                  "Subject":
                                  control.currentText.length>15?
                                      control.currentText.substring(0,12)+"...":
                                      control.currentText
                    }
            }
        }

        ComboBox {
            id: boxTheme
            width: parent.width
            height: boxHeight

            anchors.bottom: flowSaveList.top
            anchors.bottomMargin: 20

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
                    color: textColor
                    font.bold: true
                    text:
                        control.currentIndex===-1?
                            "Theme":
                            control.currentText.length>15?
                                control.currentText.substring(0,12)+"...":
                                control.currentText
                }
            }
        }


        Flow {
            id: flowSaveList
            width: parent.width * 3 / 4
            height: 27
            anchors.bottom: parent.bottom
            anchors.bottomMargin: verticalNotPressed-addPressed
        }
        Button {
            id: saveList
            width: flowSaveList.width
            height: flowSaveList.height - addPressed
            anchors.bottom: parent.bottom
            anchors.bottomMargin: saveList.pressed ? verticalNotPressed-addPressed : verticalNotPressed
            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "buttonADD"
            text:"ADD"
            style:  ButtonStyle {
                background: Rectangle{
                    //color: control.pressed ? "#f0b050"  : "#f0c150"
                    color: control.pressed ? "#697BBD"  : "#6988bd"
                    //color: control.pressed ? "#af0000" :"#889f0000"
                    radius: 3
                }
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pointSize: textSize - 1
                    color: "white"
                    text: control.text
                }
            }

            signal addList(string file_name)
            onClicked: saveList.addList(current_image_name)
        }

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
                PropertyChanges { target: mainImage; width: flowButtonRight.x - flowButtonLeft.x - flowButtonLeft.width }
                PropertyChanges { target: scroll; width: flowButtonRight.x - flowButtonLeft.x - flowButtonLeft.width }
                PropertyChanges { target: openPanel; source: "/assets/remove.png" }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    duration: 200;
                    properties: "anchors.rightMargin,topBarSpacing,iconSize,width,source"
                }
            }
        ]
    }
}
