#include "viewformhandler.h"

ViewFormHandler::ViewFormHandler(QObject* view) {
    mView = view;
}

ViewFormHandler::~ViewFormHandler() {}

void ViewFormHandler::onOkClicked(QString file_path) {
    FormHandler:onOkClicked(file_path);
}
