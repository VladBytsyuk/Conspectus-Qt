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
    int insertIntoListModel(QString file_name);
    bool insertIntoConspectModel(int id, int term, QString subject, QString theme);
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
    void onRemoveFile(QString file_name);
    void onAddFile(QString file_name, int term, QString subject, QString theme);


signals:
    void insertFileDBSignal(int id, QString file_name);
    void removeFileDBSignal(QString file_name);

};

#endif // CONSPECTMODEL_H
