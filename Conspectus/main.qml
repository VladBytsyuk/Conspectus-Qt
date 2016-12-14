import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 690
    height: 610
    title: qsTr("Conspectus")
    minimumWidth: 690
    minimumHeight: 610

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
            showForm.visible = false
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
            showForm.visible = false
             addForm.addFormSignal()
        }

        buttonCancel.onClicked: {
            addForm.unHighLight();
            mainForm.showMainForm();
        }
    }

    MainForm {
        id: mainForm
        anchors.fill: parent
        buttonView.onClicked: viewForm.showViewForm()
        buttonAdd.onClicked: addForm.showAddForm()

        function showMainForm() {
           viewForm.visible = false
            addForm.visible = false
           mainForm.visible = true
            showForm.visible = false
        }
    }

    ShowForm {
        id: showForm
        anchors.fill: parent
        objectName: "showForm"
        visible: false

        property string path: "file:///" + "C:\\21391.jpg"

        function showShowForm(string) {
           viewForm.visible = false
            addForm.visible = false
           mainForm.visible = false
            showForm.visible = true
        }
        buttonDiscard.onClicked: viewForm.showViewForm()
    }

}
