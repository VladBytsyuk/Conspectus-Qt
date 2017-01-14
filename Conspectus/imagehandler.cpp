#include "imagehandler.h"
#include "loggingcategories.h"
#include "filemanager.h"

#include <QPainter>
#include <QtPrintSupport>
#include <QColor>

ImageHandler::ImageHandler(QObject* view) {
    mView = view;
    forcedUpdateSubject = false;
    forcedUpdateTheme = false;
}

ImageHandler::~ImageHandler(){}

bool ImageHandler::onTurnLeft(int index, QString name) {
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
    emit imageUpdated(index, name);
    return true;
}

bool ImageHandler::onTurnRight(int index, QString name) {
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
    emit imageUpdated(index, name);
    return true;
}

bool ImageHandler::onPrint(QString name) {
    qDebug(logDebug()) << "Start printing image" << name;
    QPixmap pix;
    FileManager fm;
    pix.load(fm.getImagePath(name));
    QPrinter printer;
    QPrintDialog dlg(&printer,0);
    if (dlg.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.drawPixmap(QPoint(0, 0), pix);
        painter.end();
    }
    return true;
}

bool ImageHandler::onDelete(QString name) {
    emit deleteList(mTerm, mSubject, mTheme, name);
    returnToViewForm();
    return true;
}

bool ImageHandler::onImproveImage(int index, QString name) {
    FileManager fm;
    QImage img = fm.getImage(name).toImage();
    QImage img_preview = fm.getImagePreview(name).toImage();
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QImage new_img = division(grayScale(img), gaussianBlur(img));
    QImage new_img_preview = division(grayScale(img_preview), gaussianBlur(img_preview));
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been improved";
    updateQmlImage();
    emit imageUpdated(index, name);
    return true;
}

QImage ImageHandler::grayScale(const QImage & img) {
    if(!img.isNull()) {
        QImage image_gray = img;
        image_gray = image_gray.convertToFormat(QImage::Format_Grayscale8);
        return image_gray;
    }
    qDebug(logCritical()) << "Gray scale error";
    return QImage();
}


QImage ImageHandler::gaussianBlur(const QImage & img) {
    if(!img.isNull()) {
        int k = 15;
        int h = img.height();
        int w = img.width();
        QColor p_r,p,p_l;
        int red, green, blue;
        QImage blured_image = img;

        while (k!=0) {
            // horizontally
            for (int i=1; i<w-1; i++)
                for (int j=0; j<h; j++)
                {
                    p_l = blured_image.pixelColor(i-1,j);
                    p = blured_image.pixelColor(i,j);
                    p_r = blured_image.pixelColor(i+1,j);

                    red = (p_l.red() + p.red() + p_r.red()) / 3;
                    green = (p_l.green() + p.green() + p_r.green()) / 3;
                    blue = (p_l.blue() + p.blue() + p_r.blue()) / 3;

                    QColor p_new(red,green,blue);
                    blured_image.setPixelColor(i,j,p_new);
                }

            // vertically
            for (int i=0; i<w; i++)
                for (int j=1; j<h-1; j++)
                {
                    p_l = blured_image.pixelColor(i,j-1);
                    p = blured_image.pixelColor(i,j);
                    p_r = blured_image.pixelColor(i,j+1);

                    red = (p_l.red() + p.red() + p_r.red()) / 3;
                    green = (p_l.green() + p.green() + p_r.green()) / 3;
                    blue = (p_l.blue() + p.blue() + p_r.blue()) / 3;

                    QColor p_new(red,green,blue);
                    blured_image.setPixelColor(i,j,p_new);
                }

            k--;
        }
        return blured_image;
    }

    qDebug(logCritical()) << "Gaussian blur error";
    return QImage();
}

// Image division (first / second) (required equal first and second image size)
QImage ImageHandler::division(const QImage & first, const QImage & second) {
    if(!first.isNull() || !second.isNull()) {
        QImage result = first;
        int h = first.height();
        int w = first.width();
        QColor p_first, p_second;
        int red, green, blue;
        for (int i=0; i<w; i++) {
            for (int j=0; j<h; j++) {
                p_first = first.pixelColor(i,j);
                p_second = second.pixelColor(i,j);

                if (p_first.red() == 0)
                    p_first.setRed(1);
                if (p_second.red() == 0)
                    p_second.setRed(1);
                if (p_first.green() == 0)
                    p_first.setGreen(1);
                if (p_second.green() == 0)
                    p_second.setGreen(1);
                if (p_first.blue() == 0)
                    p_first.setBlue(1);
                if (p_second.blue() == 0)
                    p_second.setBlue(1);

                red = qMin((p_first.red() / p_second.red() * 255),255);
                green = qMin((p_first.green() / p_second.green() * 255),255);
                blue = qMin((p_first.blue() / p_second.blue() * 255),255);

                QColor p_new(red,green,blue);
                result.setPixelColor(i,j,p_new);
            }
        }
        return result;
    }
    qDebug(logCritical()) << "Image division error";
    return QImage();
}

QPixmap ImageHandler::rotate(const QPixmap & img, int degree) {
    QPoint center = img.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(degree);
    return img.transformed(matrix);
}

void ImageHandler::returnToViewForm() {
    QMetaObject::invokeMethod(mView, "showViewForm");
}

void ImageHandler::updateQmlImage() {
    QMetaObject::invokeMethod(mView, "reloadImage");
}

void ImageHandler::onSetPathToList(int term, QString subject, QString theme) {
    mTerm = term;
    mSubject = subject;
    mTheme = theme;
}

bool ImageHandler::onTagChanged(QString file_name, QString tags) {
    emit changeTag(file_name, tags);
    return true;
}

bool ImageHandler::onCommentChanged(QString file_name, QString comments) {
    emit changeComment(file_name, comments);
    return true;
}

bool ImageHandler::onSetImagePath(int index, QString file_name) {
    mPath = file_name;
    QString tag = "";
    QString comment = "";
    QStandardItemModel* model = ConspectModel::getListModel();
    int row = model->rowCount();
    for (int i = 0; i < row; ++i) {
        QModelIndex nameIndex = model->index(i, 1);
        if (nameIndex.data().toString() == file_name) {
            QModelIndex tagIndex = model->index(i, 2);
            QModelIndex commentIndex = model->index(i, 3);
            tag = tagIndex.data().toString();
            comment = commentIndex.data().toString();
        }
    }
    mView->findChild<QObject*>("tagField")->setProperty("text", tag);
    mView->findChild<QObject*>("commentField")->setProperty("text", comment);
    emit setGridViewIndex(index);
    return true;
}

void ImageHandler::onForm() {
    FormHandler::onForm();
}

void ImageHandler::onOkClicked(QString file_name) {
    emit addConspectListToAnotherPath(mCurrentTerm, mCurrentSubject, mCurrentTheme, file_name);
}

void ImageHandler::onPathChange() {

}
