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
    property string textColor: "#263238"

    function unHighLight() {
        rectTextField.state = ""
        boxTerm.state = ""
        boxSubject.state = ""
        boxTheme.state = ""
    }

    //forced emit subjectSelect signal
    function emitSubjectSelect(subject) {
        boxSubject.subjectSelect(subject);
    }

    //forced emit themeSelect signal
    function emitThemeSelect(theme) {
        boxTheme.themeSelect(theme);
    }

    function startTimer() {
        greenTimer.start();
    }

    Component {
        id: buttonStyle
        ButtonStyle {

            background: Rectangle{
//                border.color: control.hovered ? "#F09750" : "#f0c150"
//                border.width: control.pressed ? 3 : 2
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

        Rectangle{
            id: rectTextField
            objectName: "rectEditText"
            color:"#00000000"
            width: boxWidth + 1
            height: boxHeight + 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: -70
            anchors.verticalCenter: parent.verticalCenter
            radius: 4

            TextField {
                id: textField1
                objectName: "editText"
                width: boxWidth
                height: boxHeight
                placeholderText: qsTr("File Path")
                inputMethodHints: Qt.ImhNoAutoUppercase
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
            states: [
                State {
                    name: "highlight"
                    PropertyChanges {
                        target: dropShadowTextField
                        color: "#8f0000"
                        horizontalOffset: 0
                        verticalOffset: 0
                    }
                },
                State {
                    name: "highlightGreen"
                    PropertyChanges {
                        target: dropShadowTextField
                        color: "#aa008f00"
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 10
                        samples: 21
                    }
                }
            ]
        }
        DropShadow {
            id: dropShadowTextField
            anchors.fill: rectTextField
            source: rectTextField
            color: "#50000000"
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            samples: 17
        }
    }

    FileDialog {
            id: fileDialog
            title: "Select a file"
            folder: shortcuts.pictures
            nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
            selectedNameFilter: "Image files (*.png *.jpg)"
            onAccepted: {
                var path = utils.convertUrlToNativeFilePath(fileDialog.fileUrl)
                textField1.text = "";
                textField1.insert(0, path);
            }
            onRejected: { console.log("Rejected") }
        }

    Button {
        id: buttonBrowse
        width: 70
        height: boxHeight
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: buttonBrowse.pressed ? 152 : 150
        anchors.verticalCenterOffset: buttonBrowse.pressed ? -68 : -70
        anchors.verticalCenter: parent.verticalCenter
        text:"Browse"
        states: State {
            name: "highlight"
            PropertyChanges {target: dropShadowBrowse; color: "#9f0000";
                            horizontalOffset: -10; verticalOffset: 0;}
        }
        visible: true
        style:  ButtonStyle {
            background: Rectangle{
                color: control.pressed ? "#F0AE50"  : "#f0c150"
                radius: 3
            }
            label: Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                //font.pointSize: 8
                font.bold: true
                color: "black"
                text: control.text
            }
        }
        onClicked: fileDialog.open()
    }

    DropShadow {
        id: dropShadowBrowse
        anchors.fill: buttonBrowse
        source: buttonBrowse
        color: "#50000000"
        horizontalOffset: buttonBrowse.pressed ? 1 : 3
        verticalOffset: buttonBrowse.pressed ? 1 : 3
        //horizontalOffset: buttonOk.pressed ? shadowOffset-addPressed : shadowOffset
        //verticalOffset: buttonOk.pressed ? shadowOffset-addPressed : shadowOffset
        radius: buttonBrowse.hovered ? rOffShadowNotPressed+3 : rOffShadowNotPressed

        samples: 17
    }

    property alias buttonOk: buttonOk
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
            id: buttonOk
            width: buttonWidth
            height: buttonHeight
            objectName: "buttonOk"

            signal okClicked(string path)
            onClicked: buttonOk.onClick()

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonOk.pressed ? -horizontalNotPressed+addPressed : -horizontalNotPressed
            anchors.bottom: parent.bottom
            anchors.bottomMargin: buttonOk.pressed ? verticalNotPressed-addPressed : verticalNotPressed
            text:"OK"
            visible: true
            style: buttonStyle

            function onClick() {
                var isEditTextEmpty = textField1.text == "";
                var isTermEmpty = boxTerm.editText === "" || boxTerm.editText < 1;
                var isSubjectEmpty = boxSubject.editText === "";
                var isThemeEmpty = boxTheme.editText === "";
                if (isEditTextEmpty) {
                    rectTextField.state = "highlight"
                } else {
                    rectTextField.state = ""
                }
                if (isTermEmpty) {
                    boxTerm.state = "highlight";
                } else {
                    boxTerm.state = ""
                }
                if (isSubjectEmpty) {
                    boxSubject.state = "highlight"
                } else {
                    boxSubject.state = ""
                }
                if (isThemeEmpty) {
                     boxTheme.state = "highlight"
                } else {
                    boxTheme.state = ""
                 }
                if (!isEditTextEmpty && !isTermEmpty && !isSubjectEmpty && !isThemeEmpty) {
                    buttonOk.okClicked(textField1.text)
                }
            }
        }

        Timer {
            id: greenTimer
            interval: 500
            onTriggered: rectTextField.state = ""
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
        anchors.fill: buttonOk
        source: buttonOk
        color: "#50000000"
        horizontalOffset: buttonOk.pressed ? shadowOffset-addPressed : shadowOffset
        verticalOffset: buttonOk.pressed ? shadowOffset-addPressed : shadowOffset
        radius: buttonOk.hovered ? rOffShadowNotPressed+8 : rOffShadowNotPressed
        samples: 17
    }

    ComboBox {
        id: boxTerm
        objectName: "boxTerm"
        width: boxWidth
        height: boxHeight

        signal termSelect(string term)

        Component.onCompleted: {
            currentIndex = -1
        }

        states: State {
            name: "highlight"
            PropertyChanges {target: dropShadowTerm; color: "#9f0000";
                             horizontalOffset: 0; verticalOffset: 0;}
        }

        editable: true
        //onCurrentTextChanged: boxTerm.termSelect(model[currentIndex])
        onEditTextChanged: boxTerm.termSelect(boxTerm.editText.toString())

        inputMethodHints: Qt.ImhNoAutoUppercase
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -30
        anchors.verticalCenter: parent.verticalCenter
        style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#9f0000"
                }
                label: Text {                    
                    renderType: Text.NativeRendering
                    font.bold: true
                    color: textColor
                    text: control.currentIndex===-1?"Term":
                          control.currentText
                }
        }
    }

    ComboBox {
        id: boxSubject
        width: boxWidth
        height: boxHeight
        objectName: "boxSubject"

        signal subjectSelect(string subject)

        Component.onCompleted: {
            currentIndex = -1
        }

        states: State {
            name: "highlight"
            PropertyChanges {target: dropShadowSubject; color: "#af0000";
                            horizontalOffset: 0; verticalOffset: 0;}
        }

        editable: true
        //onCurrentTextChanged: boxSubject.subjectSelect(model[currentIndex])
        onEditTextChanged: boxSubject.subjectSelect(boxSubject.editText.toString())

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 10
        anchors.verticalCenter: parent.verticalCenter
        style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#af0000"
                }
                label: Text {
                    //renderType: Text.NativeRendering
                    font.bold: true
                    color: textColor
                    text: control.currentIndex===-1?"Subject":control.currentText
                }
        }
    }

    ComboBox {
        id: boxTheme
        width: boxWidth
        height: boxHeight
        objectName: "boxTheme"

        signal themeSelect(string theme)

        Component.onCompleted: {
            currentIndex = -1
        }

        states: State {
            name: "highlight"
            PropertyChanges {target: dropShadowTheme; color: "#bf0000";
                horizontalOffset: 0; verticalOffset: 0}
        }

        editable: true
        //onCurrentTextChanged: boxTheme.themeSelect(model[currentIndex])
        onEditTextChanged: boxTheme.themeSelect(boxTheme.editText.toString())

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 50
        anchors.verticalCenter: parent.verticalCenter
        style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#bf0000"
                }
                label: Text {
                    renderType: Text.NativeRendering
                    color: "white"
                    font.bold: true
                    text:
                        control.currentIndex===-1?"Theme":control.currentText
                }
        }
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
    Text {
        id: title
        text: "ADD LIST"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -150
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 28
        font.bold: true
        color: textColor
    }

    Text {
        width: boxWidth
        height: boxHeight
        anchors.right: boxTerm.left
        anchors.rightMargin: 10
        anchors.verticalCenterOffset: -30
        anchors.verticalCenter: parent.verticalCenter

        horizontalAlignment: TextInput.AlignRight
        verticalAlignment: TextInput.AlignVCenter

        text: "Term"
        color: textColor
        font.pixelSize: 12
        font.family: "Helvetica"

    }

    Text {
        width: boxWidth
        height: boxHeight
        anchors.right: boxSubject.left
        anchors.rightMargin: 10
        anchors.verticalCenterOffset: 10
        anchors.verticalCenter: parent.verticalCenter

        horizontalAlignment: TextInput.AlignRight
        verticalAlignment: TextInput.AlignVCenter

        text: "Subject"
        color: textColor
        font.pixelSize: 12
        font.family: "Helvetica"
    }

    Text {
        width: boxWidth
        height: boxHeight
        anchors.right: boxTheme.left
        anchors.rightMargin: 10
        anchors.verticalCenterOffset: 50
        anchors.verticalCenter: parent.verticalCenter

        horizontalAlignment: TextInput.AlignRight
        verticalAlignment: TextInput.AlignVCenter
        text: "Theme"
        color: textColor
        font.family: "Helvetica"
        font.pixelSize: 12
    }
}
