#include "dbmanager.h"

bool DBManager::makeQuery(QString queryString)
{
    QSqlQuery query;
    bool isQueryDone = query.exec(queryString);
    if (!isQueryDone) {
        qDebug() << "Couldn't exec this query:" << endl << queryString << endl;
    }
    return isQueryDone;
}

bool DBManager::createDB()
{
    QSqlDatabase conspectDataBase = QSqlDatabase::addDatabase("QSQLITE");
    conspectDataBase.setDatabaseName(DATABASE_NAME);
    if (!conspectDataBase.open()) {
        qDebug() << "Couldn't open database." << endl;
        return false;
    }

    QString createConspectTableQuery =
        "CREATE TABLE " TABLE_CONSPECT " ("
            TERM " integer" ","
            SUBJECT " VARCHAR(255)" ","
            THEME " VARCHAR(255)" ","
            LIST_ID " integer"
        ");";
    makeQuery(createConspectTableQuery);

    QString createListTableQuery =
        "CREATE TABLE " TABLE_LIST " ("
            LIST_ID " integer PRIMARY KEY NOT NULL" ","
            FILE_NAME " VARCHAR(255)" ","
            TAGS " VARCHAR(255)" ","
            COMMENTS " VARCHAR(255)"
        ");";
    makeQuery(createListTableQuery);




}

DBManager::DBManager()
{
    if (createDB()) {
        //do something
    };
}
