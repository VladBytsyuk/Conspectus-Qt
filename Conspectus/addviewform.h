#ifndef ADDVIEWFORM_H
#define ADDVIEWFORM_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>
#include"conspectmodel.h"

class AddViewForm
{
private:
    QObject* mView;
    int getTermRowInModel(int term);

public:
    AddViewForm(QObject* view);

    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(QString subject);
};

#endif // ADDVIEWFORM_H
