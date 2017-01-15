#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "formhandler.h"

class ImageHandler : public FormHandler
{
    Q_OBJECT

protected:
    void onPathChange();

private:
    int mTerm;
    QString mSubject;
    QString mTheme;
    QString mPath;
    QImage grayScale(const QImage & name);
    QImage division(const QImage & first, const QImage & second);
    QPixmap rotate(const QPixmap & img, int degree);
    void updateQmlImage();
    void returnToViewForm();

public:
    ImageHandler(QObject* view);
    ~ImageHandler();

public slots:
    void onSetPathToList(int term, QString subject, QString theme);
    bool onTurnLeft(int index, QString name);
    bool onTurnRight(int index, QString name);
    bool onImproveImage(int index, QString name);
    bool onPrint(QString name);
    bool onDelete(QString name);
    bool onTagChanged(QString file_name, QString tags);
    bool onCommentChanged(QString file_name, QString comment);
    bool onSetImagePath(int index, QString file_name);
    bool onCropImage(int index, QString name, int fromX, int fromY, int toX, int toY);

    void onForm();
    void onOkClicked(QString file_path);
signals:
    void imageUpdated(int index, QString name);
    void deleteList(int term, QString subject, QString theme, QString file_name);
    void addConspectListToAnotherPath(int term, QString subject, QString theme, QString file_name);
    void changeTag(QString file_name, QString tag);
    void changeComment(QString file_name, QString comment);
    void setGridViewIndex(int index);
};

#endif // IMAGEHANDLER_H
