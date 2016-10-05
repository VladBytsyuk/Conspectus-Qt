#ifndef CONSPECTMODEL_H
#define CONSPECTMODEL_H

#include<QStandardItemModel>

class ConspectModel
{
private:
    /* ==================== Constructor ==================== */
    ConspectModel() {
        conspectHierarchyModel = new QStandardItemModel();
        listsModel = new QStandardItemModel();
    }


    /* ====================== Fields ======================= */
    static ConspectModel* mInstance;
    QStandardItemModel* conspectHierarchyModel;
    QStandardItemModel* listsModel;
    
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
};



/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;

#endif // CONSPECTMODEL_H
