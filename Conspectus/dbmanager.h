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
    static DBManager* getInstance() {
        if (mInstance == nullptr) {
            mInstance = new DBManager();
        }
        return mInstance;
    }
    
    void setModel() {
        QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
        QStandardItemModel* listModel = ConspectModel::getListModel();

        clearTable(TABLE_CONSPECT);
        clearTable(TABLE_LIST);

        int termsAmount = conspectModel->rowCount();
        for (int termIterator = 0; termIterator < termsAmount; ++termIterator) {
            QModelIndex termIndex = conspectModel->index(termIterator, 0);
            int term = termIndex.data().toInt();

            int subjectsAmount = conspectModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjectsAmount; ++subjectIterator) {
                QModelIndex subjectIndex =
                        conspectModel->index(subjectIterator, 0, termIndex);
                QString subject = subjectIndex.data().toString();

                int themesAmount = conspectModel->rowCount(subjectIndex);
                for (int themeIterator = 0; themeIterator < themesAmount; ++themeIterator) {
                    QModelIndex themeIndex =
                            conspectModel->index(themeIterator, 0, subjectIndex);
                    QString theme = themeIndex.data().toString();
                    QModelIndex themeNumberIndex =
                            conspectModel->index(themeIterator, 0, subjectIndex);
                    int themeNumber = themeNumberIndex.data().toInt();

                    int listsAmount = conspectModel->rowCount(themeIndex);
                    for (int listIterator = 0; listIterator < listsAmount; ++listIterator) {
                        QModelIndex listIndex =
                                conspectModel->index(listIterator, 0, themeIndex);
                        int listId = listIndex.data().toInt();
                        QModelIndex listNumberIndex =
                                conspectModel->index(listIterator, 1, themeIndex);
                        int listNumber = listNumberIndex.data().toInt();
                        QModelIndex idIndex =
                                conspectModel->index(listIterator, 2, themeIndex);
                        int id = idIndex.data().toInt();

                        QString insertQuery =
                                "INSERT INTO " TABLE_CONSPECT " VALUES"
                                    "(" + QString::number(id) + ", "
                                    + QString::number(term) + ", '"
                                    + subject + "', "
                                    + QString::number(themeNumber) + ", '"
                                    + theme + "', "
                                    + QString::number(listNumber) + ", "
                                    + QString::number(listId) + ")";
                        makeQuery(insertQuery);
                    }
                }
            }
        }

        int listTableSize = listModel->rowCount();
        for (int rowIterator = 0; rowIterator < listTableSize; ++rowIterator) {
            QModelIndex listIdIndex = listModel->index(rowIterator, 0);
            QModelIndex fileNameIndex = listModel->index(rowIterator, 1);
            QModelIndex tagIndex = listModel->index(rowIterator, 2);
            QModelIndex commentsIndex = listModel->index(rowIterator, 3);

            int listId = listIdIndex.data().toInt();
            listId = listId == -1 ? generateListId() : listId;
            QString fileName = fileNameIndex.data().toString();
            QString tag = tagIndex.data().toString();
            QString comments = commentsIndex.data().toString();

            QString insertQuery =
                    "INSERT INTO " TABLE_LIST " VALUES"
                        "(" + QString::number(listId) + ", '"
                        + fileName + "', '" + tag + "', '" + comments + "')";
            makeQuery(insertQuery);
        }
    };

    void insertRowIntoTableConspect(int id,
                                    int term,
                                    QString subject,
                                    int theme_no, QString theme,
                                    int list_id_no, int list_id) {
        QString isTableContain =
                "SELECT COUNT(*) "
                    "FROM " TABLE_CONSPECT " "
                    "WHERE " CONSPECT_ID " = " + QString::number(id);
        QSqlQuery countQuery = makeQuery(isTableContain);
        countQuery.next();
        int count = countQuery.value(0).toInt();
        if (count == 0) {
            QString insertQuery =
                    "INSERT INTO " TABLE_CONSPECT " "
                        "VALUES(" + QString::number(id) + ", "
                        + QString::number(term) + ", '"
                        + subject + "', "
                        + QString::number(theme_no) + ", '"
                        + theme + "', "
                        + QString::number(list_id_no) + ", "
                        + QString::number(list_id) + ")";
            makeQuery(insertQuery);
        } else {
            QString updateQuery =
                    "UPDATE " TABLE_CONSPECT " "
                        "SET " TERM " = " + QString::number(term) + ", "
                            SUBJECT " = '" + subject + "', "
                            THEME_NO " = " + QString::number(theme_no) + ", "
                            THEME " = '" + theme + "', "
                            LIST_ID_NO " = " + QString::number(list_id_no) + ", "
                            LIST_ID " = " + QString::number(list_id) + " "
                        "WHERE " CONSPECT_ID " = " + QString::number(id);
            makeQuery(updateQuery);
        }
    }

    void deleteRowFromTable(int rowId, QString tableName) {
        QString idName = QString::compare(tableName, TABLE_CONSPECT, Qt::CaseInsensitive) == 0 ?
                    CONSPECT_ID : LIST_ID;
        QString deleteQuery =
                "DELETE FROM " + tableName + " "
                    "WHERE " + idName  + " = " + QString::number(rowId);
        makeQuery(deleteQuery);
    }

    void insertRowIntoTableList(int list_id,
                                QString file_name,
                                QString tags,
                                QString comments) {
        QString isTableContain =
                "SELECT COUNT(*) "
                    "FROM " TABLE_LIST " "
                    "WHERE " LIST_ID " = " + QString::number(list_id);
        QSqlQuery countQuery = makeQuery(isTableContain);
        countQuery.next();
        int count = countQuery.value(0).toInt();
        if (count == 0) {
            QString insertQuery =
                    "INSERT INTO " TABLE_LIST " "
                        "VALUES(" + QString::number(list_id) + ", '"
                        + file_name + "', '"
                        + tags + "', '"
                        + comments + "')";
            makeQuery(insertQuery);
        } else {
            QString updateQuery =
                    "UPDATE " TABLE_LIST " "
                        "SET " FILE_NAME " = '" + file_name + "', "
                            TAGS " = '" + tags + "', "
                            COMMENTS " = '" + comments + "' "
                        "WHERE " LIST_ID " = " + QString::number(list_id);
            makeQuery(updateQuery);
        }
    }



    int generateListId() {
        QString maxIdQuery = "SELECT MAX(" LIST_ID ") FROM " TABLE_LIST;
        QSqlQuery maxIdResult = makeQuery(maxIdQuery);
        maxIdResult.next();
        return maxIdResult.value(0).toInt();
    }

    ConspectModel* getModel() {
        QStandardItemModel* conspectModel = new QStandardItemModel(0, 3);
        QStandardItemModel* listModel = new QStandardItemModel(0, 1);

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
            conspectModel->insertColumns(0, 3, termIndex);
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
                conspectModel->insertColumns(0, 3, subjIndex);
                for (int themeIterator = 0; themes.next(); ++themeIterator) {
                    QString theme = themes.value(0).toString();
                    QModelIndex themeIndex =
                            conspectModel->index(themeIterator, 0, subjIndex);
                    conspectModel->setData(themeIndex, theme);

                    QString getThemeNumber =
                            "SELECT " THEME_NO " "
                                "FROM " TABLE_CONSPECT " "
                                "WHERE " TERM " = " + QString::number(term) + " "
                                "AND " SUBJECT " = '" + subject + "' "
                                "AND " THEME " = '" + theme + "'";
                    QSqlQuery themeNo = makeQuery(getThemeNumber);
                    themeNo.next();
                    int themeNumber = themeNo.value(0).toInt();
                    QModelIndex themeNumberIndex =
                            conspectModel->index(themeIterator, 1, subjIndex);
                    conspectModel->setData(themeNumberIndex, themeNumber);

                    QString getListId =
                            "SELECT DISTINCT " LIST_ID ", " CONSPECT_ID " "
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
                    conspectModel->insertColumns(0, 3, themeIndex);
                    for (int listIterator = 0; lists.next(); ++listIterator) {
                        QModelIndex listIndex =
                                conspectModel->index(listIterator, 0, themeIndex);
                        int listId = lists.value(0).toInt();

                        QModelIndex idIndex =
                                conspectModel->index(listIterator, 2, themeIndex);
                        int id = lists.value(1).toInt();

                        QString getListIdNumber =
                                "SELECT DISTINCT " LIST_ID_NO " "
                                    "FROM " TABLE_CONSPECT " "
                                    "WHERE " TERM " = " + QString::number(term) + " "
                                    "AND " SUBJECT " = '" + subject + "' "
                                    "AND " THEME " = '" + theme + "' "
                                    "AND " LIST_ID " = " + QString::number(listId);
                        QSqlQuery listNumberQuery = makeQuery(getListIdNumber);
                        listNumberQuery.next();
                        QModelIndex listNumberIndex =
                                 conspectModel->index(listIterator, 1, themeIndex);
                        int listNumber = listNumberQuery.value(0).toInt();

                        conspectModel->setData(listIndex, listId);
                        conspectModel->setData(listNumberIndex, listNumber);
                        conspectModel->setData(idIndex, id);                      
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


#endif // DBMANAGER_H
