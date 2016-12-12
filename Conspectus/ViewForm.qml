import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int shadowOffset: 5
    property int boxWidth: 195
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
            text:"EDIT"
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
            id: flowTopBarText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            width: 600
            height: 30
            spacing: 5

            Text {
                width: boxWidth
                height: boxHeight
                horizontalAlignment: TextInput.AlignHCenter
                text: "Term"
                font.pixelSize: 12
            }

            Text {
                width: boxWidth
                height: boxHeight
                horizontalAlignment: TextInput.AlignHCenter
                text: "Subject"
                font.pixelSize: 12
            }

            Text {
                width: boxWidth
                height: boxHeight
                horizontalAlignment: TextInput.AlignHCenter
                text: "Theme"
                font.pixelSize: 12
            }
        }

        Flow {
            id: flowTopBar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            width: 600
            height: 30
            spacing: 5

            ComboBox {
                id: boxTerm
                width: boxWidth
                height: boxHeight
                objectName: "boxTerm"
                model: [1,2,3,4,5,6,7,8]
                Component.onCompleted: {
                    currentIndex = -1
                }

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
                width: boxWidth
                height: boxHeight
                objectName: "boxSubject"
                model: ["Maths","Economics","Physics","English"]
                Component.onCompleted: {
                    currentIndex = -1
                }

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
                width: boxWidth
                height: boxHeight
                objectName: "boxTheme"
                model: ["Limits","Summs"]
                Component.onCompleted: {
                    currentIndex = -1
                }

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

        } //End Top bar
    }

    /**
    * Photo bar
    */
    Rectangle {
        id: photoBar
        width: parent.width - 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: topBar.bottom
        anchors.topMargin: 10
        anchors.bottom: flowEditCancel.top
        anchors.bottomMargin: 10
        border.color: "#006988bd"
        color: "#006988bd"
        radius: 3

        ListModel {
            id: listModel

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }

            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
            ListElement {
                src: "K:\IMGL5314.jpg"
                list_no: 1
            }
        }

        Component {
            id: delegateId
            Rectangle {
                id: delegateArea
                width: 130
                height: 140
                radius: 3
                color: delegateMA.containsMouse ? "#70B9C9E4" : "#00B9C9E4"

                signal openingPicture(string path)

                states: State {
                            name: "Set100%color"
                            PropertyChanges { target: delegateArea; color: "#B9C9E4" }
                        }
                        State {
                            name: "Set70%color"
                            PropertyChanges { target: delegateArea; color: "#70B9C9E4" }
                        }
                        State {
                            name: "Set0%color"
                            PropertyChanges { target: delegateArea; color: "#00B9C9E4" }
                        }

                Image {
                    id: delegateImage
                    anchors.fill: parent
                    anchors.topMargin: 10
                    anchors.bottomMargin: 20
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    source: "file:///" + src;
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    text: list_no
                    anchors.horizontalCenter: delegateImage.horizontalCenter
                    anchors.top: delegateImage.bottom
                    anchors.topMargin: 5
                }

                MouseArea {
                    id: delegateMA
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    hoverEnabled: true
                    onClicked: {
                        if (mouse.button & Qt.RightButton) {
                            gridView.currentIndex = index;
                        } else if (mouse.button & Qt.LeftButton) {
                            gridView.currentIndex = index;
                        }
                    }
                    onDoubleClicked: {
                        if (mouse.button & Qt.RightButton) {
                            gridView.currentIndex = index;
                        } else if (mouse.button & Qt.LeftButton) {
                            showForm.showImage(src);
                            showForm.showShowForm();
                            //delegateArea.openingPicture(src);
                            gridView.currentIndex = index;
                        }
                    }
                }

            }
        }

        Component {
            id: highlight
            Rectangle {
                color: "#B9C9E4"
                radius: 3
                width: gridView.currentItem.width
                height: gridView.currentItem.height
                //x: gridView.currentItem.x
                //y: gridView.currentItem.y
                //Behavior on x { SpringAnimation { spring: 5; damping: 0.2 } }
                //Behavior on y { SpringAnimation { spring: 5; damping: 0.2 } }
            }
        }

        ScrollView {
            id: scrollBar
            width: parent.width
            height: parent.height

            flickableItem.interactive: true
            verticalScrollBarPolicy : Qt.ScrollBarAsNeeded

            Keys.onUpPressed: scrollBar.decrease()
            Keys.onDownPressed: scrollBar.increase()

            focus: true

            /*style: ScrollViewStyle {
                    transientScrollBars: true
                    handle: Item {
                        implicitWidth: 14
                        implicitHeight: 26
                        Rectangle {
                            color: "#424246"
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 4
                            anchors.rightMargin: 4
                            anchors.bottomMargin: 6
                        }
                    }
                    scrollBarBackground: Item {
                        implicitWidth: 14
                        implicitHeight: 26
                    }
            }*/

            GridView {
                anchors.fill: parent
                cellWidth: 130
                cellHeight: 150
                highlight: highlight
                highlightFollowsCurrentItem: true
                focus: true

                id: gridView

                model: listModel

                delegate: delegateId

            }
       }
   }

   Flow {
       id: flowEditCancel
       width: parent.width
       height: buttonHeight + 15
       anchors.bottom: parent.bottom
       anchors.bottomMargin: 2
       anchors.horizontalCenter: parent.horizontalCenter
       //Rectangle { color: "red"; width: parent.width; height: parent.height}
   }
}
