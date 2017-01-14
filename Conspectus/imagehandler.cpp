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

bool ImageHandler::onGreyscale(int index, QString name) {
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
    emit imageUpdated(index, name);
    return true;
}

bool ImageHandler::onDelete(QString name) {
    emit deleteList(mTerm, mSubject, mTheme, name);
    returnToViewForm();
    return true;
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

QPixmap ImageHandler::greyscale(const QPixmap & img) {
    QImage t_img = img.toImage();
    for( int w = 0; w <= t_img.rect().right(); w++ ) {
        for( int h = 0; h <= t_img.rect().bottom(); h++ ) {
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
