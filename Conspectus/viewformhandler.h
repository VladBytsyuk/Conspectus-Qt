#ifndef VIEWFORMHANDLER_H
#define VIEWFORMHANDLER_H

#include "formhandler.h"

class ViewFormHandler : public FormHandler
{
    Q_OBJECT

public:
    ViewFormHandler(QObject* view);
    ~ViewFormHandler();

public slots:
    void onOkClicked(QString file_path);
};

#endif // VIEWFORMHANDLER_H
