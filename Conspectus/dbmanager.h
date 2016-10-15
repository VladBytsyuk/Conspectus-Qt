#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>
#include "conspectmodel.h"

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
                     << queryString;
        }
        return query;
    }
    bool fillAssets() {
        QString insertMathIntro =
            "INSERT INTO " TABLE_CONSPECT " "
                "VALUES(13, 1, 'Mathematic', 1, 'Intro', 1, 12);";
        makeQuery(insertMathIntro);

        QString insertMathLimits =
            "INSERT INTO " TABLE_CONSPECT " "
                "VALUES(14, 1, 'Mathematic', 2, 'Limits', 1, 12);";
        makeQuery(insertMathLimits);

        QString insertEngGreetings =
            "INSERT INTO " TABLE_CONSPECT " "
                "VALUES(15, 2, 'English', 1, 'Greetings', 1, 32);";
        makeQuery(insertEngGreetings);

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
                CONSPECT_ID " integer PRIMARY KEY NOT NULL" ","
                TERM " integer NOT NULL" ","
                SUBJECT " VARCHAR(255) NOT NULL" ","
                THEME_NO " integer NOT_NULL" ","
                THEME " VARCHAR(255) NOT NULL" ","
                LIST_ID_NO " integer NOT_NULL" ","
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
        query = makeQuery("SELECT COUNT(*) FROM " + tableName);
        query.next();
        return query.value(0).toInt() == 0;
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
    
    void setModel(ConspectModel* model);

    ConspectModel* getModel() {
        QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
        QStandardItemModel* listModel = ConspectModel::getListModel();

        QString getTerms = "SELECT DISTINCT " TERM " "
                               "FROM " TABLE_CONSPECT;
        QSqlQuery terms = makeQuery(getTerms);
        QString termsCount = "SELECT COUNT(DISTINCT " TERM ") "
                                 "FROM " TABLE_CONSPECT;
        QSqlQuery termsSize = makeQuery(termsCount);
        termsSize.next();
        conspectModel->insertRows(0, termsSize.value(0).toInt(),
                                  conspectModel->index(0,0));
        for (int termIterator = 0; terms.next(); ++termIterator) {
            QModelIndex termIndex = conspectModel->index(termIterator, 0);
            int term = terms.value(0).toInt();
            conspectModel->setData(termIndex, term);

            QString getSubjects =
                    "SELECT DISTINCT " SUBJECT " "
                        "FROM " TABLE_CONSPECT " "
                        "WHERE " TERM " = " + QString::number(term);
            QSqlQuery subjects = makeQuery(getSubjects);
            QString subjectsCount =
                    "SELECT COUNT(DISTINCT " SUBJECT ") "
                        "FROM " TABLE_CONSPECT " "
                        "WHERE " TERM " = " + QString::number(term);
            QSqlQuery subjectsSize = makeQuery(subjectsCount);
            subjectsSize.next();
            conspectModel->insertRows(0, subjectsSize.value(0).toInt(),
                                      termIndex);
            conspectModel->insertColumns(0, 1, termIndex);
            for (int subjIterator = 0; subjects.next(); ++subjIterator) {
                QString subject = subjects.value(0).toString();
                QModelIndex subjIndex =
                        conspectModel->index(subjIterator, 0, termIndex);
                conspectModel->setData(subjIndex, subject);

                QString getThemes =
                        "SELECT DISTINCT " THEME " "
                            "FROM " TABLE_CONSPECT " "
                            "WHERE " TERM " = " + QString::number(term) + " "
                            "AND " SUBJECT " = '" + subject + "' "
                            "ORDER BY " THEME_NO;
                QSqlQuery themes = makeQuery(getThemes);
                QString themesCount =
                        "SELECT COUNT(DISTINCT " THEME ") "
                            "FROM " TABLE_CONSPECT " "
                            "WHERE " TERM " = " + QString::number(term) + " "
                            "AND " SUBJECT " = '" + subject + "'";
                QSqlQuery themesSize = makeQuery(themesCount);
                themesSize.next();
                conspectModel->insertRows(0, themesSize.value(0).toInt(),
                                          subjIndex);
                conspectModel->insertColumns(0, 1, subjIndex);
                for (int themeIterator = 0; themes.next(); ++themeIterator) {
                    QString theme = themes.value(0).toString();
                    QModelIndex themeIndex =
                            conspectModel->index(themeIterator, 0, subjIndex);
                    conspectModel->setData(themeIndex, theme);

                    QString getListId =
                            "SELECT DISTINCT " LIST_ID " "
                                "FROM " TABLE_CONSPECT " "
                                "WHERE " TERM " = " + QString::number(term) + " "
                                "AND " SUBJECT " = '" + subject + "' "
                                "AND " THEME " = '" + theme + "' "
                                "ORDER BY " LIST_ID_NO;
                    QSqlQuery lists = makeQuery(getListId);
                    QString listsCount =
                            "SELECT COUNT(DISTINCT " LIST_ID ") "
                                "FROM " TABLE_CONSPECT " "
                                "WHERE " TERM " = " + QString::number(term) + " "
                                "AND " SUBJECT " = '" + subject + "' "
                                "AND " THEME " = '" + theme + "'";
                    QSqlQuery listsSize = makeQuery(listsCount);
                    listsSize.next();
                    conspectModel->insertRows(0, listsSize.value(0).toInt(),
                                              themeIndex);
                    conspectModel->insertColumns(0, 1, themeIndex);
                    for (int listIterator = 0; lists.next(); ++listIterator) {
                        QModelIndex listIndex =
                                conspectModel->index(listIterator, 0, themeIndex);
                        int listId = lists.value(0).toInt();
                        conspectModel->setData(listIndex, listId);
                    }

                }

            }

        }

        QSqlQuery listTable = makeQuery("SELECT * FROM " TABLE_LIST);
        QSqlQuery listTableCount = makeQuery("SELECT COUNT(*) FROM " TABLE_LIST);
        listTableCount.next();
        int listTableSize = listTableCount.value(0).toInt();
        listModel->insertRows(0, listTableSize);
        listModel->insertColumns(0, 3);
        for (int listTableIterator = 0; listTable.next(); ++listTableIterator) {
            int listId = listTable.value(0).toInt();
            QModelIndex idIndex = listModel->index(listTableIterator, 0);
            listModel->setData(idIndex, listId);

            QString fileName = listTable.value(1).toString();
            QModelIndex fileIndex = listModel->index(listTableIterator, 1);
            listModel->setData(fileIndex, fileName);

            QString tags = listTable.value(2).toString();
            QModelIndex tagsIndex = listModel->index(listTableIterator, 2);
            listModel->setData(tagsIndex, tags);

            QString comments = listTable.value(3).toString();
            QModelIndex commentsIndex = listModel->index(listTableIterator, 3);
            listModel->setData(commentsIndex, comments);
        }

        ConspectModel* model =  ConspectModel::getInstance();
        ConspectModel::setConspectModel(conspectModel);
        ConspectModel::setListModel(listModel);
        return model;
    }
};



/* ================= Fields initialization ================= */
DBManager* DBManager::mInstance = nullptr;

#endif // DBMANAGER_H
