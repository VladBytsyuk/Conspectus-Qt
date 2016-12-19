#include "resourceimageprovider.h"
#include <QImage>
#include <QPixmap>

#include <QDebug>

#include "filemanager.h"

ResourceImageProvider::ResourceImageProvider(QQuickImageProvider::ImageType type) : QQuickImageProvider(type) {}

ResourceImageProvider::~ResourceImageProvider() {}

QImage ResourceImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    FileManager fm;
    QString absolute_path = fm.getSourceDirPath() + "/" + id;
    QImage image = fm.getImage(absolute_path);
    QImage result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();

    return result;
}

QPixmap ResourceImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QString rsrcid = ":/" + id;
    QPixmap image(rsrcid);
    QPixmap result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}
