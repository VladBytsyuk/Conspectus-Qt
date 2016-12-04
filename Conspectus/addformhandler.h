#ifndef ADDFORM_H
#define ADDFORM_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>
#include "conspectmodel.h"

class AddFormHandler : public QObject
{
    Q_OBJECT
private:
    QString mCurrentFilePath;
    int mCurrentTerm;
    QString mCurrentSubject;
    QString mCurrentTheme;


    QObject* mView;
    int getTermRowInModel(int term);
    int getSubjectRowInModel(int term_row, QString subject);

public:
    AddFormHandler(QObject* view);
    ~AddFormHandler();

    bool setTerms();
    bool setSubjects(int term);
    bool setThemes(int term, QString subject);

signals:
    void tryToAddFileToFileSystem(QString file_path);
    void addFileToModel(QString file_name, int term, QString subject, QString theme);

public slots:
    void onAddForm();
    void onSetTerm(QString term);
    void onSetSubject(QString subject);
    void onSetTheme(QString theme);
    void onOkClicked(QString file_path);

    void onInvalidFilePath();
    void onValidFilePath(QString file_name);

};

#endif // ADD_FORM_H
