#ifndef VIEWFORMHANDLER_H
#define VIEWFORMHANDLER_H

#include "formhandler.h"

class ViewFormHandler : public FormHandler
{
    Q_OBJECT

private:
    QList<int> getListIds(int term, QString subject, QString theme);
    QStringList getFileNames(const QList<int> &listIds);
    bool invokeSetImages();
    void changeModelOrdering(int previous_index, int current_index);
    void reloadGridView();

public:
    ViewFormHandler(QObject* view);
    ~ViewFormHandler();

    QStringList getImageSources(int term, QString subject, QString theme);
    void setImageToQml(QString file_name, int list_no);
    void clearViewsFromView();

signals:
    void changeOrder(int term, QString subject, QString theme, int previous_index, int current_index);

public slots:
    void onSetTheme(QString theme);
    void onOkClicked(QString file_path);
    void onOrderChanged(int previous_index, int current_index);
};

#endif // VIEWFORMHANDLER_H
