#include "imagehandler.h"
#include "loggingcategories.h"
#include "filemanager.h"

#include <QPainter>
#include <QColor>

ImageHandler::ImageHandler(QObject * view) : mView(view) {}

ImageHandler::~ImageHandler(){}

bool ImageHandler::onTurnLeft(QString name) {
    FileManager fm;
    QPixmap img = fm.getImage(name);
    QPixmap img_preview = fm.getImagePreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QPixmap new_img = rotate(img, 270);
    QPixmap new_img_preview = rotate(img_preview, 270);
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been rotated to the left";
    updateQmlImage();
    emit imageUpdated(name);
    return true;
}

bool ImageHandler::onTurnRight(QString name) {
    FileManager fm;
    QPixmap img = fm.getImage(name);
    QPixmap img_preview = fm.getImagePreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QPixmap new_img = rotate(img, 90);
    QPixmap new_img_preview = rotate(img_preview, 90);
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been rotated to the right";
    updateQmlImage();
    emit imageUpdated(name);
    return true;
}

bool ImageHandler::onPrint(QString name) {
    qDebug(logDebug()) << "Start printing image" << name;
    return true;
}

bool ImageHandler::onGreyscale(QString name) {
    FileManager fm;
    QPixmap img = fm.getImage(name);
    QPixmap img_preview = fm.getImagePreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QPixmap new_img = greyscale(img);
    QPixmap new_img_preview = greyscale(img_preview);
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been grayscaled";
    updateQmlImage();
    emit imageUpdated(name);
    return true;
}


QPixmap ImageHandler::rotate(const QPixmap & img, int degree) {
    QPoint center = img.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(degree);
    return img.transformed(matrix);
}

QPixmap ImageHandler::greyscale(const QPixmap & img) {
    QImage t_img = img.toImage();
    for( int w = 0; w < t_img.rect().right(); w++ ) {
        for( int h = 0; h < t_img.rect().bottom(); h++ ) {
            QColor col( t_img.pixel(w,h) );
            col.setHsv(col.hue(), 0, col.value() * 0.8, col.alpha());
            t_img.setPixel(w,h,col.rgb());
        }
    }
    return QPixmap::fromImage(t_img);
}

void ImageHandler::updateQmlImage() {
    QMetaObject::invokeMethod(mView, "reloadImage");
}
