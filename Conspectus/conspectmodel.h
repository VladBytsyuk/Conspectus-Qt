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
    int generateConspectId();
    int generateListNo(int term, QString subject, QString theme);
    int getThemeNo(int term, QString subject, QString theme);
    int insertIntoListModel(QString file_name);
    bool insertIntoConspectModel(int id, int term, QString subject, QString theme);
    bool insertIntoConspectModel(int id, int term, QString subject, int theme_no,
                                 QString theme, int list_no, int list_id);
    bool insertList(QModelIndex* index, int id, int list_no, int list_id);
    bool insertTheme(QModelIndex* index, int theme_no, QString theme,
                                    int id, int list_no, int list_id);
    bool insertSubject(QModelIndex* index, QString subject, int theme_no, QString theme,
                                      int id, int list_no, int list_id);
    bool insertTerm(int term, QString subject, int theme_no,
                                   QString theme, int id, int list_no, int list_id);
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
