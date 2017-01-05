#include "utils.h"
#include <QDir>
#include <QUrl>
#include "filemanager.h"

Util::Util(QObject *parent) : QObject(parent) {}

QString Util::convertUrlToNativeFilePath(const QUrl &urlStylePath) const
{
    return QDir::toNativeSeparators(urlStylePath.toLocalFile());
}
