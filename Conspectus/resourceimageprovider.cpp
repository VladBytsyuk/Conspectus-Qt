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
    QImage image;// = fm.getImage(id);
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
    FileManager fm;
    QPixmap image = fm.getImage(id);
    QPixmap result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}
