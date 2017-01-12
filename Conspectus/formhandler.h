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
    int mCurrentTerm = -1;
    QString mCurrentSubject;
    QString mCurrentTheme;

    QObject* mView;

    bool forcedUpdateSubject;
    bool forcedUpdateTheme;

    int getTermRowInModel(int term);
    int getSubjectRowInModel(int term_row, QString subject);

    bool clearComboBoxes();

public:
    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(int term, QString subject);


public slots:
    virtual void onForm();
    void onSetTerm(QString term);
    void onSetSubject(QString subject);
    virtual void onSetTheme(QString theme);
    virtual void onOkClicked(QString file_path) = 0;
};

#endif // FORMHANDLER_H
