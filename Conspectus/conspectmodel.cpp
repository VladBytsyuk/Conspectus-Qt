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

int ConspectModel::generateListId() {
    int max_id = -1;
    for (int row = 0; row < mListsModel->rowCount(); ++row) {
        QModelIndex rowIndex = mListsModel->index(row, 0);
        int id = rowIndex.data().toInt();
        max_id = id > max_id ? id : max_id;
    }
    return max_id;
}

bool ConspectModel::insertFile(int id, QString file_name) {
    //TODO:
    return true;
}

bool ConspectModel::removeFile(QString file_name) {
    //TODO:
    return true;
}

void ConspectModel::onInsertFile(QString file_name) {
    int id = generateListId();
    this->insertFile(id, file_name);
    emit insertFileDBSignal(id, file_name);
}

void ConspectModel::onRemoveFile(QString file_name) {
    this->removeFile(file_name);
    emit removeFileDBSignal(file_name);
}

/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel =
        new QStandardItemModel(0, 3);
QStandardItemModel* ConspectModel::mListsModel =
        new QStandardItemModel(0, 1);
