#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "formhandler.h"

class ImageHandler : public FormHandler
{
    Q_OBJECT

private:
    int mTerm;
    QString mSubject;
    QString mTheme;
    QString mPath;

    QPixmap rotate(const QPixmap & img, int degree);
    QPixmap greyscale(const QPixmap & img);
    void updateQmlImage();
    void returnToViewForm();

public:
    ImageHandler(QObject* view);
    ~ImageHandler();

public slots:
    void onSetPathToList(int term, QString subject, QString theme);
    bool onTurnLeft(QString name);
    bool onTurnRight(QString name);
    bool onGreyscale(QString name);
    bool onPrint(QString name);
    bool onDelete(QString name);
    bool onTagChanged(QString file_name, QString tags);
    bool onCommentChanged(QString file_name, QString comment);
    bool onSetImagePath(QString file_name);

    void onForm();
    void onOkClicked(QString file_path);
signals:
    void imageUpdated(QString name);
    void deleteList(int term, QString subject, QString theme, QString file_name);
    void addConspectListToAnotherPath(int term, QString subject, QString theme, QString file_name);
    void changeTag(QString file_name, QString tag);
    void changeComment(QString file_name, QString comment);
};

#endif // IMAGEHANDLER_H
