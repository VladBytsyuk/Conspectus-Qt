#ifndef VIEWFORMHANDLER_H
#define VIEWFORMHANDLER_H

#include "formhandler.h"

class ViewFormHandler : public FormHandler
{
    Q_OBJECT

private:
    QMap<int, QString> getListIds(int term, QString subject, QString theme);
    QMap<int, QString> getFileNames(QMap<int, QString> &images);
    bool invokeSetImages();
    void changeModelOrdering(int previous_index, int current_index);
    void reloadGridView();

public:
    ViewFormHandler(QObject* view);
    ~ViewFormHandler();

    QMap<int, QString> getImageSources(int term, QString subject, QString theme);
    void setImageToQml(QString file_name, int list_no);
    void clearViewsFromView();

signals:
    void changeOrder(int term, QString subject, QString theme, int previous_index, int current_index);
    void setPathToList(int term, QString subject, QString theme);

public slots:
    void onSetPath();
    void onSetTheme(QString theme);
    void onOkClicked(QString file_path);
    void onOrderChanged(int previous_index, int current_index);
    void onUpdateImage(QString name);
    void onUpdateView();
};

#endif // VIEWFORMHANDLER_H
