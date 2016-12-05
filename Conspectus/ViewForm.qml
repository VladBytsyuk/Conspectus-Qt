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


    Component {
        id: buttonStyle
        ButtonStyle {

            background: Rectangle{
                border.color: "#f0c150"
                border.width: control.hovered ? 2 : 1
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
            anchors.horizontalCenterOffset: 120
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            text:"EDIT"
            visible: true
            style: buttonStyle
        }

    DropShadow {
        anchors.fill: buttonCancel
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
        width: parent.width - 30
        height: 259
        anchors.centerIn: parent
        spacing: 10
        Rectangle { color: "red"; width: 120; height: 80 }
        Rectangle { color: "green"; width: 80; height: 120 }
        Rectangle { color: "blue"; width: 80; height: 120 }
        Rectangle { color: "yellow"; width: 120; height: 80 }
        Rectangle { color: "black"; width: 80; height: 120 }
    }

    Flow {
        id: flow2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -20
        width: 600
        height: 30
        Rectangle { color: "#00f0c150"; width: 600; height: 30 }
        spacing: 5
        //___________________________________________________________________________
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
     //__________________________________________________________________________________

    }

}
