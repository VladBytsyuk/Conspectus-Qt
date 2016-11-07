#ifndef CONSPECTMODEL_H
#define CONSPECTMODEL_H

#include <QStandardItemModel>

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
    

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static ConspectModel* getInstance();

    static void setConspectModel(QStandardItemModel* conspectModel);
    static QStandardItemModel* getConspectModel();


    static void setListModel(QStandardItemModel* listModel);
    static QStandardItemModel* getListModel();

private slots:
    void onAddFile(QString file_name){
//        dbManager->insertRowIntoTableList(dbManager->generateListId(), file_name);
    }

    void onRemoveFile(QString file_name){
//        dbManager->deleteRowFromTable(dbManager->findFileIdByName(file_name), TABLE_LIST);
    }

};

#endif // CONSPECTMODEL_H
