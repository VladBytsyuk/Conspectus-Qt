#include "dbmanager.h"

DBManager::DBManager()
{
    tryToCreateDB();
    if (isTableEmpty(TABLE_CONSPECT) && isTableEmpty(TABLE_LIST)) {
        fillAssets();
    }
}

/*======================= Private Methods ====================================*/

QSqlQuery DBManager::makeQuery(QString queryString) {
    QSqlQuery query;
    bool isQueryDone = query.exec(queryString);
    if (!isQueryDone) {
        qDebug() << "Couldn't exec this query:" << endl
                 << queryString;
    }
    return query;
}
bool DBManager::fillAssets() {
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
bool DBManager::tryToCreateDB() {
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
bool DBManager::isTableEmpty(QString tableName) {
    QSqlQuery query;
    query = makeQuery("SELECT COUNT(*) FROM " + tableName);
    query.next();
    return query.value(0).toInt() == 0;
}
void DBManager::clearTable(QString tableName) {
    QString query = "DELETE FROM " + tableName;
    makeQuery(query);
}


/* ================= Fields initialization ================= */
DBManager* DBManager::mInstance = nullptr;
