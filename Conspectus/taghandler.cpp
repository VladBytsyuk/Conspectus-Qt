#include "taghandler.h"
#include "loggingcategories.h"

TagHandler::TagHandler(QObject *view) {

}

TagHandler::~TagHandler(){}

bool TagHandler::onSearchRequest(QString request) {
    qDebug(logDebug()) << "Incoming request is" << request;
}
