#include "utils.h"
#include <QDir>
#include <QUrl>

Util::Util(QObject *parent) : QObject(parent) {}

QString Util::convertUrlToNativeFilePath(const QUrl &urlStylePath) const
{
    return QDir::toNativeSeparators(urlStylePath.toLocalFile());
}
