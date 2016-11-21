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
    int getSubjectRowInModel(int term_row, QString subject);

public:
    AddViewForm(QObject* view);

    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(int term, QString subject);
};

#endif // ADDVIEWFORM_H
