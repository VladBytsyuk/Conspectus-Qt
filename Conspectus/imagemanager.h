#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>

class ImageManager : public QObject
{
    Q_OBJECT
private:
	QImage* image;

public:
	ImageManager(QImage* image, QObject *parent = 0);
	~ImageManager();



signals:

public slots:
};

#endif // IMAGEMANAGER_H