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
    QString currentRequest;

    void setImageToQml(QString file_name, int list_no);
    void clearViewsFromView();
    bool invokeSetImages(QStringList images);
    void reloadGridView();

signals:

public slots:
    bool onSearchRequest(QString request);
};

#endif // TAGHANDLER_H
