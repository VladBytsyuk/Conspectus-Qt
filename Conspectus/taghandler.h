#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include <QObject>

class TagHandler : public QObject
{
    Q_OBJECT
public:
    explicit TagHandler(QObject* view);
    ~TagHandler();

private:
    QObject* mView;

    void setImageToQml(QString file_name, int list_no);
    void clearViewsFromView();
    bool invokeSetImages(QStringList images);

signals:

public slots:
    bool onSearchRequest(QString request);
};

#endif // TAGHANDLER_H
