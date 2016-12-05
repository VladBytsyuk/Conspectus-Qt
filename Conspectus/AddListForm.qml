import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int shadowOffset: 5
    property int boxWidth: 200
    property int boxHeight: 25


    Component {
        id: buttonStyle
        ButtonStyle {

            background: Rectangle{
                color: "#6988bd"
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

//    Rectangle {
//        anchors.fill: parent
//        color: "#f6f6f6"

//        TextField {
//            id: textField1
//            width: boxWidth
//            height: boxHeight
//            placeholderText: qsTr("Text Field")
//            inputMethodHints: Qt.ImhNoAutoUppercase
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenterOffset: -70
//            anchors.verticalCenter: parent.verticalCenter
//        }
//    }

//    Button {
//        id: buttonBrowse
//        width: 70
//        height: boxHeight
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.horizontalCenterOffset: 150
//        anchors.verticalCenterOffset: -70
//        anchors.verticalCenter: parent.verticalCenter
//        text:"Browse"
//        visible: true
//        style:  ButtonStyle {
//            background: Rectangle{
//                color: "#f0c150"
//                radius: 3
//            }
//            label: Text {
//                renderType: Text.NativeRendering
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                font.family: "Helvetica"
//                //font.pointSize: 8
//                font.bold: true
//                color: "black"
//                text: control.text
//            }
//        }
//    }

//    DropShadow {
//        anchors.fill: buttonBrowse
//        source: buttonBrowse
//        color: "#50000000"
//        horizontalOffset: 3
//        verticalOffset: 3
//        radius: 8
//        samples: 17
//    }
    
    property alias buttonEdit: buttonEdit
    property alias buttonCancel: buttonBack

        Button {
            id: buttonBack
            width: buttonWidth
            height: buttonHeight
            text: "Back"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 120
//            anchors.verticalCenterOffset: 180
//            anchors.verticalCenter: parent.verticalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            visible: true            
            style: buttonStyle
        }

        Button {
            id: buttonEdit
            width: buttonWidth
            height: buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -120
//            anchors.verticalCenterOffset: 180
//            anchors.verticalCenter: parent.verticalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            text:"Edit"
            visible: true
            style: buttonStyle
        }

    DropShadow {
        anchors.fill: buttonBack
        source: buttonCancel
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
        radius: 8
        samples: 17
    }

    DropShadow {
        anchors.fill: buttonEdit
        source: buttonEdit
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
        radius: 8
        samples: 17
    }

    Text {
        id: title
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -160
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
        font.bold: true
    }

    Flow {
        id: flowFoto
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 600
        height: 259
        anchors.centerIn: parent
        spacing:2
        Rectangle { color: "red"; width: 600; height: 10 }
        Rectangle { color: "green"; width: 120; height: 50 }
        Rectangle { color: "blue"; width: 215; height: 80 }
        Rectangle { color: "yellow"; width: 50; height: 50 }
        Rectangle { color: "black"; width: 410; height: 10 }
    }

    Flow {
        id: flow2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 600
        height: 30
        Rectangle { color: "red"; width: 600; height: 30 }

        //___________________________________________________________________________
        ComboBox {
            id: boxTerm
            width: boxWidth
            height: boxHeight
            model: [1,2,3,4,5,6,7,8]
            Component.onCompleted: {
                currentIndex = -1
            }
            inputMethodHints: Qt.ImhNoAutoUppercase
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenterOffset: -50
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            style: ComboBoxStyle {
                    background: Rectangle {
                        radius: 3
                        color: "#f0c150"
                    }
                    label: Text {
                        renderType: Text.NativeRendering
                        font.bold: true
                        color: "white"
                        text: control.currentIndex===-1?"Term":control.currentText
                    }
            }
        }

        ComboBox {
            id: boxSubject
            width: boxWidth
            height: boxHeight
            model: ["Maths","Economics","Physics","English"]
            Component.onCompleted: {
                currentIndex = -1
            }
            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenterOffset: -10
            anchors.verticalCenter: parent.verticalCenter

            style: ComboBoxStyle {
                    background: Rectangle {
                        radius: 3
                        color: "#f0c150"
                    }
                    label: Text {
                        renderType: Text.NativeRendering
                        font.bold: true
                        color: "white"
                        text: control.currentIndex===-1?"Subject":control.currentText
                    }
            }
        }

        ComboBox {
            id: boxTheme
            width: boxWidth
            height: boxHeight
            model: ["Limits","Summs"]
            Component.onCompleted: {
                currentIndex = -1
            }
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenterOffset: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            style: ComboBoxStyle {
                    background: Rectangle {
                        radius: 3
                        color: "#f0c150"
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
     //__________________________________________________________________________________

    }

}
