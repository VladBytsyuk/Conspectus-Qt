#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

#define DATABASE_NAME "conspectus_db"

#define TABLE_CONSPECT "table_conspect"
#define TERM "term"
#define SUBJECT "subject"
#define THEME "theme"
#define LIST_ID "list_id"

#define TABLE_LIST "table_list"
#define FILE_NAME "file_name"
#define TAGS "tags"
#define COMMENTS "comments"

using namespace std;

class DBManager
{    
private:
    /* ==================== Constructor ==================== */
    DBManager() {
        if (createDB()) {
            fillAssets();
        }
    }


    /* ====================== Fields ======================= */
    static DBManager* mInstance;


    /* ====================== Methods ====================== */
    bool makeQuery(QString queryString) {
        QSqlQuery query;
        bool isQueryDone = query.exec(queryString);
        if (!isQueryDone) {
            qDebug() << "Couldn't exec this query:" << endl
                     << queryString << endl;
        }
        return isQueryDone;
    }
    bool fillAssets() {
        QString insertMathIntro =
            "INSERT INTO " TABLE_CONSPECT " "
                "VALUES(1, 'Mathematic', 'Intro', 12);";
        makeQuery(insertMathIntro);

        QString insertMathLimits =
            "INSERT INTO " TABLE_CONSPECT " "
                "VALUES(1, 'Mathematic', 'Limits', 12);";
        makeQuery(insertMathLimits);

        QString insertMathList =
            "INSERT INTO " TABLE_LIST " "
                "VALUES(12, 'abc.jpg', 'math:', 'cool theme');";
        makeQuery(insertMathList);

        return true;
    }
    bool createDB() {
        QSqlDatabase conspectDataBase = QSqlDatabase::addDatabase("QSQLITE");
        conspectDataBase.setDatabaseName(DATABASE_NAME);
        if (!conspectDataBase.open()) {
            qDebug() << "Couldn't open database." << endl;
            return false;
        }

        QString createConspectTableQuery =
            "CREATE TABLE " TABLE_CONSPECT " ("
                TERM " integer NOT NULL" ","
                SUBJECT " VARCHAR(255) NOT NULL" ","
                THEME " VARCHAR(255) NOT NULL" ","
                LIST_ID " integer NOT NULL"
            ");";
        makeQuery(createConspectTableQuery);

        QString createListTableQuery =
            "CREATE TABLE " TABLE_LIST " ("
                LIST_ID " integer PRIMARY KEY NOT NULL" ","
                FILE_NAME " VARCHAR(255) NOT NULL" ","
                TAGS " VARCHAR(255)" ","
                COMMENTS " VARCHAR(255)"
            ");";
        makeQuery(createListTableQuery);
        return true;
    }

public:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */

    /* ====================== Methods ====================== */
    static DBManager* getInstance() {
        if (mInstance == nullptr) {
            mInstance = new DBManager();
        }
        return mInstance;
    }
};



/* ================= Fields initialization ================= */
DBManager* DBManager::mInstance = nullptr;

#endif // DBMANAGER_H
