#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QString>
#include <QtSql>
#include <QStandardItemModel>
#include "loggingcategories.h"
//#include "conspectmodel.h"
//#include "filemanager.h"

#define DATABASE_NAME "conspectus_db"

#define TABLE_CONSPECT "table_conspect"
#define CONSPECT_ID "id"
#define TERM "term"
#define SUBJECT "subject"
#define THEME_NO "theme_no"
#define THEME "theme"
#define LIST_ID_NO "list_id_no"
#define LIST_ID "list_id"

#define TABLE_LIST "table_list"
#define FILE_NAME "file_name"
#define TAGS "tags"
#define COMMENTS "comments"

using namespace std;

class DBManager:public QObject
{    
    Q_OBJECT
private:
    /* ==================== Constructor ==================== */
    DBManager();

    /* ====================== Fields ======================= */
    static DBManager* mInstance;


    /* ====================== Methods ====================== */
    QSqlQuery makeQuery(QString queryString);
    bool fillAssets();
    bool tryToCreateDB();
    bool isTableEmpty(QString tableName);
    void clearTable(QString tableName);

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static DBManager* getInstance();
    //void setModel();
    void insertRowIntoTableConspect(int id,
                                    int term,
                                    QString subject,
                                    int theme_no, QString theme,
                                    int list_id_no, int list_id);

    void deleteRowFromTable(int rowId, QString tableName);
    void insertRowIntoTableList(int list_id,
                                QString file_name,
                                QString tags = QString(),
                                QString comments = QString());
    void updateRowInTableConspect(int id,
                                  int term,
                                  QString subject,
                                  int theme_no, QString theme,
                                  int list_id_no, int list_id);
    //ConspectModel* getModel();
    //int generateListId();
    int findFileIdByName(QString file_name);
    QStandardItemModel* getConspectModel();
    QStandardItemModel* getListModel();

public slots:
    void onInsertFileIntoListTable(int id, QString file_name);
	void onRemoveFile(QString file_name);

    void onInsertListIntoConspectTable(int id,
                      int term,
                      QString subject,
                      int theme_no, QString theme,
                      int list_id_no, int list_id);
    void onUpdateRowInConspectTable(int id,
                               int term,
                               QString subject,
                               int theme_no, QString theme,
                               int list_id_no, int list_id);
};


#endif // DBMANAGER_H
