import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQml.Models 2.2

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


    property alias buttonCancel: buttonCancel

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

    /**
    * Top bar
    */
    Rectangle {
        id: topBar
        width: parent.width - 16
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#006988bd"
        radius: 3

        /**
        * Top bar text
        */
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

        /**
        * Top bar buttons
        */
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
        objectName: "photoBar"
        width: parent.width - 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: topBar.bottom
        anchors.topMargin: 10
        anchors.bottom: flowEditCancel.top
        anchors.bottomMargin: 10
        //border.color: "#6988bd"
        color: "#006988bd"
        radius: 3

        function onSetImageToQml(fileName, list_no) {
            listModel.append({ "src": fileName, "list_no": list_no });
        }

        function clearView(smth) {
            listModel.clear();
        }


        /**
        * Grid highlight
        */
        Component {
            id: highlight
            Rectangle {
                color: "#B9C9E4"
                radius: 3
                width: root.currentItem.width
                height: root.currentItem.height
            }
        }

        /**
        * Grid scroll view + grid body
        */
        ScrollView {
            id: scrollBar
            width: parent.width
            height: parent.height
            verticalScrollBarPolicy : Qt.ScrollBarAsNeeded
            flickableItem.interactive: true
            focus: true

            GridView {
                id: root
                objectName: "gridView"
                width: 320; height: 480
                anchors.fill: parent
                cellWidth: 130; cellHeight: 150
                highlight: highlight
                highlightFollowsCurrentItem: true
                focus: true

                signal orderChanged(int prevIndex, int currIndex);
                signal setPath();

                displaced: Transition {
                    NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
                }

                model: DelegateModel {
                    id: visualModel
                    model: ListModel {
                        id: listModel
                        objectName: "listModel"
                    }
                    delegate: MouseArea {
                        id: delegateRoot
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true

                        property bool held: false
                        property int  lastDraggedIndex: -1
                        property int  visualIndex: DelegateModel.itemsIndex

                        width: root.cellWidth; height: root.cellHeight
                        drag.target:  held ? icon : undefined

                        Rectangle {
                            id: icon
                            width: 125; height: 145
                            anchors {
                                horizontalCenter: parent.horizontalCenter;
                                verticalCenter: parent.verticalCenter
                            }

                            radius: 3
                            color: delegateRoot.containsMouse ? "#70B9C9E4" : "#00B9C9E4"
                            //border.color: "black"

                            Drag.active: delegateRoot.drag.active
                            Drag.source: delegateRoot
                            Drag.hotSpot.x: 36
                            Drag.hotSpot.y: 36

                            states: [
                                State {
                                    when: icon.Drag.active
                                    ParentChange {
                                        target: icon
                                        parent: root
                                    }

                                    AnchorChanges {
                                        target: icon;
                                        anchors.horizontalCenter: undefined;
                                        anchors.verticalCenter: undefined
                                    }
                                }
                            ]

                            /**
                            * Delegate image
                            */
                            Image {
                                id: delegateImage
                                anchors.fill: parent
                                anchors.topMargin: 10
                                anchors.bottomMargin: 20
                                anchors.leftMargin: 10
                                anchors.rightMargin: 10
                                source: "image://sourceDir/Preview/" + src;
                                fillMode: Image.PreserveAspectFit
                                opacity: parent.opacity
                                cache: false
                            }

                            /**
                            * Delegate text
                            */
                            Text {
                                text: list_no
                                anchors.horizontalCenter: delegateImage.horizontalCenter
                                anchors.top: delegateImage.bottom
                                anchors.topMargin: 5
                                opacity: parent.opacity
                            }
                        } //End icon


                        DropArea {
                            anchors { fill: parent; margins: 15 }

                            onEntered: visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex);
                        }

                        onClicked: {
                            if (mouse.button & Qt.RightButton || mouse.button & Qt.LeftButton) {
                                root.currentIndex = index;
                            }
                        }

                        onDoubleClicked: {
                            if (mouse.button & Qt.LeftButton) {
                                root.currentIndex = index;
                                if (root.currentIndex - 1 != -1 && root.currentIndex + 1 != root.count) {
                                    showForm.setSource(src, true, true);
                                } else if (root.currentIndex - 1 === -1 && root.currentIndex + 1 != root.count) {
                                    showForm.setSource(src, false, true);
                                } else if (root.currentIndex - 1 != -1 && root.currentIndex + 1 === root.count) {
                                    showForm.setSource(src, true, false);
                                } else {
                                    showForm.setSource(src, false, false);
                                }
                                showForm.showShowForm();
                                root.setPath();
                            }
                        }

                        onPressAndHold: {
                            held = true;
                            icon.opacity = 0.7;
                            lastDraggedIndex = index;
                        }

                        onReleased: {
                            held = false;
                            icon.opacity = 1;
                            console.log(lastDraggedIndex + " " + delegateRoot.visualIndex);
                            if (lastDraggedIndex != -1 &&
                                    delegateRoot.visualIndex != -1 &&
                                    lastDraggedIndex != delegateRoot.visualIndex) {
                                root.orderChanged(lastDraggedIndex, delegateRoot.visualIndex);
                            }
                        }
                    }
                }
            }

       }
   } // End photo bar

    /**
    * Bottom bar
    */
   Flow {
       id: flowEditCancel
       width: parent.width
       height: buttonHeight + 15
       anchors.bottom: parent.bottom
       anchors.bottomMargin: 2
       anchors.horizontalCenter: parent.horizontalCenter
   } //End bottom bar

   function setNextImage() {
       console.log(root.currentIndex + 1);

       if (root.currentIndex + 1 != root.count) {
           var nextImg = listModel.get(root.currentIndex + 1).src;
           root.currentIndex = root.currentIndex + 1;
           if (root.currentIndex - 1 != -1 && root.currentIndex + 1 != root.count) {
               showForm.setSource(nextImg, true, true);
           } else if (root.currentIndex - 1 === -1 && root.currentIndex + 1 != root.count) {
               showForm.setSource(nextImg, false, true);
           } else if (root.currentIndex - 1 != -1 && root.currentIndex + 1 === root.count) {
               showForm.setSource(nextImg, true, false);
           } else {
               showForm.setSource(nextImg, false, false);
           }
       }
   }

   function setPreviousImage() {
       console.log(root.currentIndex - 1);

       if (root.currentIndex - 1 != -1) {
           var prevImg = listModel.get(root.currentIndex - 1).src;
           root.currentIndex = root.currentIndex - 1;
           if (root.currentIndex - 1 != -1 && root.currentIndex + 1 != root.count) {
               showForm.setSource(prevImg, true, true);
           } else if (root.currentIndex - 1 === -1 && root.currentIndex + 1 != root.count) {
               showForm.setSource(prevImg, false, true);
           } else if (root.currentIndex - 1 != -1 && root.currentIndex + 1 === root.count) {
               showForm.setSource(prevImg, true, false);
           } else {
               showForm.setSource(prevImg, false, false);
           }
       }
   }

   function getCurrentIndex() {
       return root.currentIndex;
   }
}
