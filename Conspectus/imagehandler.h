#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QObject>

class ImageHandler : public QObject
{
    Q_OBJECT
private:
    QPixmap rotate(const QPixmap & img, int degree);
    QPixmap greyscale(const QPixmap & img);
    void updateQmlImage();

    QObject* mView;

public:
    ImageHandler(QObject *view);
    ~ImageHandler();
public slots:
    bool onTurnLeft(QString name);
    bool onTurnRight(QString name);
    bool onGreyscale(QString name);
    bool onPrint(QString name);
signals:
    void imageUpdated(QString name);
};

#endif // IMAGEHANDLER_H
