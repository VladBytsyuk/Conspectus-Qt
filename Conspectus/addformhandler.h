#ifndef ADDFORM_H
#define ADDFORM_H

#include "formhandler.h"

class AddFormHandler : public FormHandler
{
    Q_OBJECT

public:
    AddFormHandler(QObject* view);
    ~AddFormHandler();

signals:
    void tryToAddFileToFileSystem(QString file_path);
    void addFileToModel(QString file_name, int term, QString subject, QString theme);

public slots:
    void onInvalidFilePath();
    void onValidFilePath(QString file_name);

    void onOkClicked(QString file_path);

};

#endif // ADD_FORM_H
