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

    void deleteList(int term, QString subject, QString theme, QString file_name);
    void deleteList(int term, QString subject, QString theme, int list_id);
    int getListId(QString name);
    bool isImageUsed(QString name);
    bool isImageUsed(int list_id);

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static ConspectModel* getInstance();

    static void setConspectModel(QStandardItemModel* conspectModel);
    static QStandardItemModel* getConspectModel();


    static void setListModel(QStandardItemModel* listModel);
    static QStandardItemModel* getListModel();

    static void logConspectModel();
    static void logListModel();

public slots:
    void onRemoveList(int term, QString subject, QString theme, QString file_name);
    void onRemoveFile(QString file_name);
    void onAddFile(QString file_name, int term, QString subject, QString theme);
    void onChangeOrdering(int term, QString subject, QString theme, int previous_index, int current_index);
    void onAddListToAnotherPath(int term, QString subject, QString theme, QString file_name);


signals:
    void insertFileDBSignal(int id, QString file_name);
    void removeFileDBSignal(QString file_name);
    void insertListDBSignal(int id,
                            int term,
                            QString subject,
                            int theme_no, QString theme,
                            int list_id_no, int list_id);
    void updateRowInConspectTable(int id,
                   int term,
                   QString subject,
                   int theme_no, QString theme,
                   int list_id_no, int list_id);
    void removeRowFromConspectDB(int row_id);
    void tryToRemoveFile(QString file_name);

};

#endif // CONSPECTMODEL_H
