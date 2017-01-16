#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include <QObject>

class TagFormHandler : public QObject
{
    Q_OBJECT
public:
    explicit TagFormHandler(QObject* view);
    ~TagFormHandler();

private:
    QObject* mView;
    QString currentRequest;
    int mIndex;

    void setImageToQml(QString file_name, int list_no);
    void clearViewsFromView();
    bool invokeSetImages(QStringList images);
    void reloadGridView();

signals:

public slots:
    bool onSearchRequest(QString request);
    void onSetGridViewIndex(int index);
    void onForm();
};

#endif // TAGHANDLER_H
