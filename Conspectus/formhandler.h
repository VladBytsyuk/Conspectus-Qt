#ifndef FORMHANDLER_H
#define FORMHANDLER_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>
#include "conspectmodel.h"

class FormHandler: public QObject
{
    Q_OBJECT

protected:
    QString mCurrentFilePath;
    int mCurrentTerm;
    QString mCurrentSubject;
    QString mCurrentTheme;

    QObject* mView;

    int getTermRowInModel(int term);
    int getSubjectRowInModel(int term_row, QString subject);

public:
    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(int term, QString subject);

public slots:
    void onForm();
    void onSetTerm(QString term);
    void onSetSubject(QString subject);
    void onSetTheme(QString theme);
    virtual void onOkClicked(QString file_path);
};

#endif // FORMHANDLER_H
