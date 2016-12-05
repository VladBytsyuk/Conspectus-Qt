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

    Rectangle {
        anchors.fill: parent
        color: "#f6f6f6"
    }
    
    property alias buttonOk: buttonOk
    property alias buttonCancel: buttonCancel

        Button {
            id: buttonCancel
            width: buttonWidth
            height: buttonHeight
            text: "CANCEL"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 120
            anchors.verticalCenterOffset: 180
            anchors.verticalCenter: parent.verticalCenter
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
            anchors.horizontalCenterOffset: -120
            anchors.verticalCenterOffset: 180
            anchors.verticalCenter: parent.verticalCenter
            text:"OK"
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
        anchors.fill: buttonOk
        source: buttonOk
        color: "#50000000"
        horizontalOffset: shadowOffset
        verticalOffset: shadowOffset
        radius: 8
        samples: 17
    }



    ComboBox {
        id: boxTerm
        width: boxWidth
        height: boxHeight
        model: [1,2,3,4,5,6,7,8]
        objectName: "boxTerm"

        signal termSelect(string term)

        Component.onCompleted: {
            currentIndex = -1
        }
        onCurrentTextChanged: boxTerm.termSelect(model[currentIndex])

        inputMethodHints: Qt.ImhNoAutoUppercase
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#9f0000"
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
        objectName: "boxSubject"

        signal subjectSelect(string subject)

        Component.onCompleted: {
            currentIndex = -1
        }
        onCurrentTextChanged: boxSubject.subjectSelect(model[currentIndex])

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -10
        anchors.verticalCenter: parent.verticalCenter
        style: ComboBoxStyle {
                background: Rectangle {
                    radius: 3
                    color: "#af0000"
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
        objectName: "boxTheme"

        signal themeSelect(string theme)

        Component.onCompleted: {
            currentIndex = -1
        }
        onCurrentTextChanged: boxTheme.themeSelect(model[currentIndex])

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 30
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
        anchors.fill: boxTerm
        source: boxTerm
        color: "#50000000"
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8
        samples: 17
    }
    DropShadow {
        anchors.fill: boxSubject
        source: boxSubject
        color: "#50000000"
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8
        samples: 17
    }
    DropShadow {
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
        text: "CONSPECTUS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -150
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 32
        font.bold: true
    }

    Canvas{
        id: arrow
//        imageLoaded: "assets/comboBox_arrow.png"
        width: 25
        height: 25
//        onPaint: {
//            var ctx = getContext("2d")
//            ctx.beginPath();
//            ctx.moveTo(x + 5, y + 10);
//            ctx.lineTo(x + 15, y + 10);
//            ctx.lineTo(x + 10, y + 15);
//            ctx.fill();
//        }
    }


}
