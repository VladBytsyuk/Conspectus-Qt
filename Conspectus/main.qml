import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Conspectus")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ViewForm {
        id : viewForm
        objectName: "viewForm"
        anchors.fill: parent;

        signal viewFormSignal()

        function showViewForm() {
           viewForm.visible = true
            addForm.visible = false
           mainForm.visible = false
           viewForm.viewFormSignal()
        }

        buttonCancel.onClicked: mainForm.showMainForm()
    }

    AddForm {
        id : addForm
        objectName: "addForm"
        anchors.fill: parent

        signal addFormSignal()

        function showAddForm(){
            viewForm.visible = false
             addForm.visible = true
            mainForm.visible = false
             addForm.addFormSignal()
        }
        buttonCancel.onClicked: mainForm.showMainForm()
    }

    MainForm {
        id: mainForm;
        anchors.fill: parent
        buttonView.onClicked: viewForm.showViewForm()
        buttonAdd.onClicked: addForm.showAddForm()

        function showMainForm() {
           viewForm.visible = false
            addForm.visible = false
           mainForm.visible = true
        }
    }

}
