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
    QStandardItemModel* mConspectHierarchyModel;
    QStandardItemModel* mListsModel;
    
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


    void setConspectModel(QStandardItemModel* conspectModel) {
        mConspectHierarchyModel = conspectModel;
    }

    QStandardItemModel* getConspectModel() {
        return mConspectHierarchyModel;
    }


    void setListModel(QStandardItemModel* listModel) {
        mListsModel = listModel;
    }

    QStandardItemModel* getListModel() {
        return mListsModel;
    }
};



/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;

#endif // CONSPECTMODEL_H
