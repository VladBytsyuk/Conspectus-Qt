#ifndef ADDVIEWFORM_H
#define ADDVIEWFORM_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>
#include"conspectmodel.h"

class AddViewForm : public QObject
{
    Q_OBJECT
private:
    int mCurrentTerm;
    QString mCurrentSubject;
    QString mCurrentTheme;

    QObject* mView;
    int getTermRowInModel(int term);
    int getSubjectRowInModel(int term_row, QString subject);

public:
    AddViewForm(QObject* view);
    ~AddViewForm();

    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(int term, QString subject);

public slots:
    void onAddForm();
    void onSetTerm(QString term);
    void onSetSubject(QString subject);
    void onSetTheme(QString theme);

};

#endif // ADDVIEWFORM_H
