#include "taghandler.h"
#include "loggingcategories.h"
#include "conspectmodel.h"

TagHandler::TagHandler(QObject *view) {

}

TagHandler::~TagHandler(){}

bool TagHandler::onSearchRequest(QString request) {
    qDebug(logDebug()) << "Incoming request is" << request;
    QStringList names = ConspectModel::getFileNamesByTag(request);
    foreach(QString str, names) {
        qDebug(logDebug()) << str;
    }
}
