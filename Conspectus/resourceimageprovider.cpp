#include "resourceimageprovider.h"
#include <QImage>
#include <QPixmap>

#include <QDebug>

ResourceImageProvider::ResourceImageProvider(QQuickImageProvider::ImageType type) :
    QQuickImageProvider(type)
{
    // This space intentionally left blank.
}

ResourceImageProvider::~ResourceImageProvider()
{
    // This space intentionally left blank.
}

QImage ResourceImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    QString rsrcid = ":/" + id;
    QImage image(rsrcid);
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
