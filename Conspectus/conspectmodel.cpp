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
    return max_id + 1;
}

int ConspectModel::insertIntoListModel(QString file_name) {
    int id = generateListId();
    int row = mListsModel->rowCount();
    mListsModel->insertRow(row);

    QModelIndex idIndex = mListsModel->index(row, 0);
    mListsModel->setData(idIndex, id);

    QModelIndex fileIndex = mListsModel->index(row, 1);
    mListsModel->setData(fileIndex, file_name);

    emit insertFileDBSignal(id, file_name);
    return id;
}

bool ConspectModel::insertIntoConspectModel(int id, int term, QString subject, QString theme) {

}

bool ConspectModel::removeFile(QString file_name) {
    int row = -1;
    int rows_count = mListsModel->rowCount();

    for (int i = 0; i < rows_count; ++i) {
        QModelIndex index = mListsModel->index(i, 1);
        if (index.data().toString() == file_name) {
            row = i;
            i = rows_count;
        }
    }
    if (row == -1) {
        qDebug() << "Can`t remove file from model, "
                 << "because model doesn't consist this file name: "
                 << file_name;
        return false;
    }
    mListsModel->removeRow(row);

    return true;
}

void ConspectModel::onRemoveFile(QString file_name) {
    this->removeFile(file_name);
    emit removeFileDBSignal(file_name);
}

void ConspectModel::onAddFile(QString file_name, int term, QString subject, QString theme) {
    int id = insertIntoListModel(file_name);
    insertIntoConspectModel(id, term, subject, theme);
}

/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel =
        new QStandardItemModel(0, 3);
QStandardItemModel* ConspectModel::mListsModel =
        new QStandardItemModel(0, 1);
