#ifndef CONSPECTMODEL_H
#define CONSPECTMODEL_H

#include<QStandardItemModel>

class ConspectModel
{
private:
    /* ==================== Constructor ==================== */
    ConspectModel() {

    }


    /* ====================== Fields ======================= */
    static ConspectModel* mInstance;
    
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

#endif // CONSPECTMODEL_H
