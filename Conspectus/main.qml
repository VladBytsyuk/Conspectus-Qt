import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

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
        anchors.fill: parent;

        function showViewForm() {
           viewForm.visible = true
            addForm.visible = false
            addListForm.visible = false
           mainForm.visible = false
        }

        buttonCancel.onClicked: mainForm.showMainForm()
        buttonOk.onClicked: addListForm.showAddListForm()
    }

    AddListForm{
        id: addListForm
        anchors.fill: parent

        function showAddListForm(){
            viewForm.visible = false
             addForm.visible = false
            addListForm.visible = true
            mainForm.visible = false
        }
        buttonCancel.onClicked: addForm.showAddForm()
    }

    AddForm{
        id : addForm
        anchors.fill: parent

        function showAddForm(){
            viewForm.visible = false
             addForm.visible = true
            addListForm.visible = false
            mainForm.visible = false
        }
        buttonCancel.onClicked: mainForm.showMainForm()
        buttonOk.onClicked: addListForm.showAddListForm()
    }

    MainForm {
        id: mainForm;
        anchors.fill: parent
        buttonView.onClicked: viewForm.showViewForm()//messageDialog.show(qsTr("View lecture"))
        buttonAdd.onClicked: addForm.showAddForm()//messageDialog.show(qsTr("Add list"))

        function showMainForm() {
           viewForm.visible = false
            addForm.visible = false
           addListForm.visible = false
           mainForm.visible = true
        }
    }

//    MessageDialog {
//        id: messageDialog
//        title: qsTr("Do it!")

//        function show(caption) {
//            messageDialog.text = caption;
//            messageDialog.open();
//        }
//    }

}
