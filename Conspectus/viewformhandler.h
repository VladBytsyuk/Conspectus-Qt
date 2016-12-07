#ifndef VIEWFORMHANDLER_H
#define VIEWFORMHANDLER_H

#include "formhandler.h"

class ViewFormHandler : public FormHandler
{
    Q_OBJECT

private:
    QList<int> getListIds(int term, QString subject, QString theme);
    QStringList getFileNames(const QList<int> &listIds);

public:
    ViewFormHandler(QObject* view);
    ~ViewFormHandler();

    QStringList getImageSources(int term, QString subject, QString theme);

public slots:
    void onOkClicked(QString file_path);
};

#endif // VIEWFORMHANDLER_H
