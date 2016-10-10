#ifndef CONSPECTMODEL_H
#define CONSPECTMODEL_H

#include <QStandardItemModel>

class ConspectModel
{
private:
    /* ==================== Constructor ==================== */
    ConspectModel() {
        mConspectHierarchyModel = new QStandardItemModel();
        mListsModel = new QStandardItemModel();
    }


    /* ====================== Fields ======================= */
    static ConspectModel* mInstance;
    static QStandardItemModel* mConspectHierarchyModel;
    static QStandardItemModel* mListsModel;
    
    /* ====================== Methods ====================== */
    

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static ConspectModel* getInstance() {
        if (mInstance == nullptr) {
            mInstance = new ConspectModel();
        }
        return mInstance;
    }


    static void setConspectModel(QStandardItemModel* conspectModel) {
        mConspectHierarchyModel = conspectModel;
    }

    static QStandardItemModel* getConspectModel() {
        return mConspectHierarchyModel;
    }


    static void setListModel(QStandardItemModel* listModel) {
        mListsModel = listModel;
    }

    static QStandardItemModel* getListModel() {
        return mListsModel;
    }
};



/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel = nullptr;
QStandardItemModel* ConspectModel::mListsModel = nullptr;

#endif // CONSPECTMODEL_H
