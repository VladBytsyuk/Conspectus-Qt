#ifndef CONSPECTMODEL_H
#define CONSPECTMODEL_H

#include <QStandardItemModel>
#include <QModelIndex>
#include "loggingcategories.h"

class ConspectModel: public QObject
{
    Q_OBJECT
private:
    /* ==================== Constructor ==================== */
    ConspectModel();


    /* ====================== Fields ======================= */
    static ConspectModel* mInstance;
    static QStandardItemModel* mConspectHierarchyModel;
    static QStandardItemModel* mListsModel;
    
    /* ====================== Methods ====================== */
    int generateListId();
    bool insertFile(int id, QString file_name);
    bool removeFile(QString file_name);

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static ConspectModel* getInstance();

    static void setConspectModel(QStandardItemModel* conspectModel);
    static QStandardItemModel* getConspectModel();


    static void setListModel(QStandardItemModel* listModel);
    static QStandardItemModel* getListModel();

public slots:
    void onInsertFile(QString file_name);
    void onRemoveFile(QString file_name);

signals:
    void insertFileDBSignal(int id, QString file_name);
    void removeFileDBSignal(QString file_name);

};

#endif // CONSPECTMODEL_H
