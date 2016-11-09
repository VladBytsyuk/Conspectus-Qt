#ifndef ADVANCEDIMAGE_H
#define ADVANCEDIMAGE_H

#include <QObject>

class AdavncedImage : public QObject
{
    Q_OBJECT
private:
	QImage* image;

public:
    AdavncedImage(QImage* image, QObject *parent = 0);
    ~AdavncedImage();



signals:

public slots:
};

#endif // ADVANCEDIMAGE_H
