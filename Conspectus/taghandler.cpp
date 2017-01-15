#include "taghandler.h"
#include "loggingcategories.h"
#include "conspectmodel.h"

TagHandler::TagHandler(QObject* view) {
  //  currentRequest = "";
    mView = view;
}

TagHandler::~TagHandler(){}

bool TagHandler::onSearchRequest(QString request) {
    qDebug(logDebug()) << "Incoming request is" << request;
    currentRequest = request;
    reloadGridView();
}

void TagHandler::setImageToQml(QString file_name, int list_no) {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "onSetImageToQml", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, file_name), Q_ARG(QVariant, list_no));
}

void TagHandler::clearViewsFromView() {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "clearView", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, empty));
}

bool TagHandler::invokeSetImages(QStringList images) {
    int number = 0;
    foreach(QString str, images) {
        setImageToQml(str, ++number);
    }
    return true;
}

void TagHandler::reloadGridView() {
    clearViewsFromView();
    invokeSetImages(ConspectModel::getFileNamesByTag(currentRequest));
    //mView->findChild<QObject*>("gridView")->setProperty("currentIndex", mIndex);
}

