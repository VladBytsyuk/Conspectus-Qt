#include "addformhandler.h"

AddFormHandler::AddFormHandler(QObject* view) {
    mView = view;
    forcedUpdateSubject = false;
    forcedUpdateTheme = false;
}

AddFormHandler::~AddFormHandler() {}


void AddFormHandler::onOkClicked(QString file_path) {
    mCurrentFilePath = file_path;
    emit tryToAddFileToFileSystem(mCurrentFilePath);
    FormHandler::onForm();
}

void AddFormHandler::onInvalidFilePath() {
    QObject *editText = mView->findChild<QObject*>("rectEditText");
    editText->setProperty("state", "highlight");
}

void AddFormHandler::onValidFilePath(QString file_name) {
    emit addFileToModel(file_name, mCurrentTerm, mCurrentSubject, mCurrentTheme);
}

void AddFormHandler::onForm() {
    clearComboBoxes();
    FormHandler::onForm();
    QObject *editText = mView->findChild<QObject*>("editText");
    editText->setProperty("text", "");
}

void AddFormHandler::onPathChange() {

}
