#include "addformhandler.h"

AddFormHandler::AddFormHandler(QObject* view) {
    mView = view;
}

AddFormHandler::~AddFormHandler() {}


void AddFormHandler::onOkClicked(QString file_path) {
    mCurrentFilePath = file_path;
    emit tryToAddFileToFileSystem(mCurrentFilePath);
    FormHandler::onForm();
}

void AddFormHandler::onInvalidFilePath() {
    //TODO: send signal to QML / invoke JS method
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
