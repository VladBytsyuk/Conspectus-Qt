import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: appWindow
    visible: true
    width: 690
    height: 610
    title: qsTr("Conspectus")
    minimumWidth: 690
    minimumHeight: 610

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: console.log("Open action triggered");
//            }
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

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
            tagForm.visible = false
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
            tagForm.visible = false
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
            tagForm.visible = false
        }
    }

    ShowForm {
        id: showForm
        anchors.fill: parent
        objectName: "showForm"
        visible: false

        signal showFormSignal()
        signal closeImage()

        function showShowForm(string) {
            viewForm.visible = false
            addForm.visible = false
            mainForm.visible = false
            showForm.visible = true
            tagForm.visible = false
            showFormSignal();
        }
        buttonCancel.onClicked: {
            if (showForm.current_source_form === "ViewForm") {
                viewForm.showViewForm();
            } else if (showForm.current_source_form === "TagForm") {
                tagForm.showTagForm();
            }
            showForm.clearTagsComments();
            showForm.current_source_form = "";
        }
    }

    TagForm {
        id: tagForm
        anchors.fill: parent
        objectName: "tagForm"
        visible: false

        signal tagFormSignal()

        function showTagForm() {
            viewForm.visible = false
            addForm.visible = false
            mainForm.visible = false
            showForm.visible = false
            tagForm.visible = true
            tagFormSignal();
        }
        buttonCancel.onClicked: {
            viewForm.showViewForm();
        }
    }

}
