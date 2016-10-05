#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>
#include <QTreeView>
#include <conspectmodel.h>

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
        tryToCreateDB();
        if (isTableEmpty(TABLE_CONSPECT) && isTableEmpty(TABLE_LIST)) {
            fillAssets();
        }
    }


    /* ====================== Fields ======================= */
    static DBManager* mInstance;


    /* ====================== Methods ====================== */
    QSqlQuery makeQuery(QString queryString) {
        QSqlQuery query;
        bool isQueryDone = query.exec(queryString);
        if (!isQueryDone) {
            qDebug() << "Couldn't exec this query:" << endl
                     << queryString << endl;
        }
        return query;
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
    bool tryToCreateDB() {
        QSqlDatabase conspectDataBase = QSqlDatabase::addDatabase("QSQLITE");
        conspectDataBase.setDatabaseName(DATABASE_NAME);
        if (!conspectDataBase.open()) {
            qDebug() << "Couldn't open database." << endl;
            return false;
        }

        QString createConspectTableQuery =
            "CREATE TABLE IF NOT EXISTS " TABLE_CONSPECT " ("
                TERM " integer NOT NULL" ","
                SUBJECT " VARCHAR(255) NOT NULL" ","
                THEME " VARCHAR(255) NOT NULL" ","
                LIST_ID " integer NOT NULL"
            ");";
        makeQuery(createConspectTableQuery);

        QString createListTableQuery =
            "CREATE TABLE IF NOT EXISTS " TABLE_LIST " ("
                LIST_ID " integer PRIMARY KEY NOT NULL" ","
                FILE_NAME " VARCHAR(255) NOT NULL" ","
                TAGS " VARCHAR(255)" ","
                COMMENTS " VARCHAR(255)"
            ");";
        makeQuery(createListTableQuery);
        return true;
    }
    bool isTableEmpty(QString tableName) {
        QSqlQuery query;
        query.prepare("SELECT * FROM " + tableName);
        return query.size() == 0;
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
    
    void setConspectModel(ConspectModel* model);

    ConspectModel* getConspectModel() {
        ConspectModel* model = ConspectModel::getInstance();
        QStandardItemModel* conspectModel = model->getConspectModel();
        QStandardItemModel* listModel = model->getListModel();
        QString getTerms = "SELECT DISTINCT " TERM " FROM " TABLE_CONSPECT ";";
        QSqlQuery terms = makeQuery(getTerms);
        for (int termIterator = 0; terms.next(); ++termIterator) {
            int term = terms.value(termIterator).toInt();
            QModelIndex termIndex = conspectModel->index(termIterator, 0);
            conspectModel->setData(termIndex, term);
        }

        QTreeView t;
        t.setModel(conspectModel);
        t.show();
        return model;
    }
};



/* ================= Fields initialization ================= */
DBManager* DBManager::mInstance = nullptr;

#endif // DBMANAGER_H
