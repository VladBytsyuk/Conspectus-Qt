#include "imagehandler.h"
#include "loggingcategories.h"
#include "filemanager.h"

#include <QPainter>
#include <QtPrintSupport>
#include <QColor>

QT_BEGIN_NAMESPACE
  extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

ImageHandler::ImageHandler(QObject* view) {
    mView = view;
    forcedUpdateSubject = false;
    forcedUpdateTheme = false;
}

ImageHandler::~ImageHandler(){}

bool ImageHandler::onTurnLeft(int index, QString name) {
    FileManager fm;
    QPixmap img = fm.getPixmap(name);
    QPixmap img_preview = fm.getPixmapPreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QPixmap new_img = rotate(img, 270);
    QPixmap new_img_preview = rotate(img_preview, 270);
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been rotated to the left";
    updateQmlImage();
    //emit imageUpdated(index, name);
    return true;
}

bool ImageHandler::onTurnRight(int index, QString name) {
    FileManager fm;
    QPixmap img = fm.getPixmap(name);
    QPixmap img_preview = fm.getPixmapPreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    QPixmap new_img = rotate(img, 90);
    QPixmap new_img_preview = rotate(img_preview, 90);
    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been rotated to the right";
    updateQmlImage();
    //emit imageUpdated(index, name);
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
    QImage img = fm.getImage(name);
    QImage img_preview = fm.getImagePreview(name);
    QString img_path = fm.getImagePath(name);
    QString img_preview_path = fm.getImagePreviewPath(name);

    //Main image
    QImage gs_img = grayScale(img);
    QImage new_gs_img = gs_img;
    QPixmap blurred_img( gs_img.size() );
    blurred_img.fill(Qt::transparent);
    {
        QPainter painter( &blurred_img );
        qt_blurImage( &painter, gs_img, 150, true, false);
    }
    QImage new_img = division(new_gs_img, blurred_img.toImage());

    //Preview image
    QImage gs_img_p = grayScale(img_preview);
    QImage new_gs_img_p = gs_img_p;
    QPixmap blurred_img_p ( gs_img_p.size() );
    blurred_img_p.fill(Qt::transparent);
    {
        QPainter painter( &blurred_img_p );
        qt_blurImage( &painter, gs_img_p, 150, true, false);
    }
    QImage new_img_preview = division(new_gs_img_p, blurred_img_p.toImage());

    new_img.save(img_path);
    new_img_preview.save(img_preview_path);

    qDebug(logDebug()) << "Image" << name << "has been improved";
    updateQmlImage();
    //emit imageUpdated(index, name);
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

                red = qMin( ( p_first.red() * 255 / (p_second.red() + 1) ) , 255 );
                green = qMin( ( p_first.green() * 255 / (p_second.green() + 1) ) , 255 );
                blue = qMin( ( p_first.blue() * 255 / (p_second.blue() + 1) ) , 255 );

                QColor p_new(red, green, blue);
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
