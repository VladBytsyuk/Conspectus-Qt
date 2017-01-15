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
    property string textColor: "#263238"

    property alias buttonCancel: buttonCancel

    signal search(string text)

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

    Rectangle {
        id: topBar
        width: parent.width - 16
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#006988bd"
        radius: 3
        //border.color: "red"

        Rectangle{
            id: textFieldRect
            objectName: "textFieldRect"
            color:"#00000000"
            width: 300
            height: parent.height / 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -30
            anchors.verticalCenter: parent.verticalCenter
            radius: 3

            TextField {
                id: textField
                objectName: "editText"
                width: parent.width
                height: parent.height
                placeholderText: qsTr("Enter tag`s name")
                inputMethodHints: Qt.ImhNoAutoUppercase
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        DropShadow {
            id: dropShadowTextField
            anchors.fill: textFieldRect
            source: textFieldRect
            color: "#50000000"
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            samples: 17
        }

        Button {
            id: buttonSearch
            width: 60
            height: textFieldRect.height
            anchors.left: textFieldRect.right
            anchors.verticalCenter: parent.verticalCenter
            text:"Search"
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
            onClicked: search(textField.text)
        }

        DropShadow {
            id: dropShadowBrowse
            anchors.fill: buttonSearch
            source: buttonSearch
            color: "#50000000"
            horizontalOffset: buttonSearch.pressed ? 1 : 3
            verticalOffset: buttonSearch.pressed ? 1 : 3
            radius: buttonSearch.hovered ? rOffShadowNotPressed+3 : rOffShadowNotPressed

            samples: 17
        }
    } //End top bar

    Rectangle {
        id: photoBar
        objectName: "photoBar"
        width: parent.width - 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: topBar.bottom
        anchors.topMargin: 10
        anchors.bottom: buttonCancel.top
        anchors.bottomMargin: 10

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

                signal setPath();

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

                        width: root.cellWidth; height: root.cellHeight

                        Rectangle {
                            id: icon
                            width: 125; height: 145
                            anchors {
                                horizontalCenter: parent.horizontalCenter;
                                verticalCenter: parent.verticalCenter
                            }

                            radius: 3
                            color: delegateRoot.containsMouse ? "#70B9C9E4" : "#00B9C9E4"

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
                                showForm.current_source_form = "TagForm";
                                showForm.showShowForm();
                                //root.setPath();
                            }
                        }

                    }
                }
            }
       }
   } // End photo bar

    function setNextImage() {
        //console.log(root.currentIndex + 1);

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
        //console.log(root.currentIndex - 1);

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
