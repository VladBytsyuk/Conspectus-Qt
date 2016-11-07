#include "conspectmodel.h"

ConspectModel::ConspectModel()
{
//    connect(&FileManager::)
    mConspectHierarchyModel = new QStandardItemModel();
    mListsModel = new QStandardItemModel();
}

ConspectModel* ConspectModel::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new ConspectModel();
    }
    return mInstance;
}

void ConspectModel::setConspectModel(QStandardItemModel* conspectModel) {
    mConspectHierarchyModel = conspectModel;
}

QStandardItemModel* ConspectModel::getConspectModel() {
    return mConspectHierarchyModel;
}


void ConspectModel::setListModel(QStandardItemModel* listModel) {
    mListsModel = listModel;
}

QStandardItemModel* ConspectModel::getListModel() {
    return mListsModel;
}

/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel =
        new QStandardItemModel(0, 3);
QStandardItemModel* ConspectModel::mListsModel =
        new QStandardItemModel(0, 1);
