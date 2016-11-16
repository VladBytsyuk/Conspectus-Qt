#ifndef ADDVIEWFORM_H
#define ADDVIEWFORM_H

#include <QObject>
#include <QList>
#include <QQuickView>
#include <QQuickItem>
#include <QStandardItemModel>
#include"conspectmodel.h"

class AddViewForm
{
private:
    QQuickView* mView;

public:
    AddViewForm(QQuickView* view);

    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(QString subject);
};

#endif // ADDVIEWFORM_H
