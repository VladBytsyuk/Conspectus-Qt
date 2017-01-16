#include "tagformhandler.h"
#include "loggingcategories.h"
#include "conspectmodel.h"

TagFormHandler::TagFormHandler(QObject* view) {
    currentRequest = "";
    mView = view;
    mIndex = 0;
}

TagFormHandler::~TagFormHandler(){}

bool TagFormHandler::onSearchRequest(QString request) {
    qDebug(logDebug()) << "Incoming request is" << request;
    mIndex = 0;
    currentRequest = request.simplified();
    reloadGridView();
    return true;
}

void TagFormHandler::setImageToQml(QString file_name, int list_no) {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "onSetImageToQml", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, file_name), Q_ARG(QVariant, list_no));
}

void TagFormHandler::clearViewsFromView() {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "clearView", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, empty));
}

bool TagFormHandler::invokeSetImages(QStringList images) {
    int number = 0;
    foreach(QString str, images) {
        setImageToQml(str, ++number);
    }
    return true;
}

void TagFormHandler::reloadGridView() {
    clearViewsFromView();
    invokeSetImages(ConspectModel::getFileNamesByTag(currentRequest));
    mView->findChild<QObject*>("gridView")->setProperty("currentIndex", mIndex);
}

void TagFormHandler::onSetGridViewIndex(int index) {
    mIndex = index;
}

void TagFormHandler::onForm() {
    mView->findChild<QObject*>("editText")->setProperty("text", currentRequest);
    reloadGridView();
}
