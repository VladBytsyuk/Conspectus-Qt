#include "dbmanager.h"

DBManager::DBManager()
{
    tryToCreateDB();
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
            "VALUES(13, 1, 'Mathematic', 1, 'Intro', 1, 13);";
    makeQuery(insertMathIntro);

    QString insertMathLimits =
        "INSERT INTO " TABLE_CONSPECT " "
            "VALUES(14, 1, 'Mathematic', 2, 'Limits', 1, 13);";
    makeQuery(insertMathLimits);

    QString insertEngGreetings =
        "INSERT INTO " TABLE_CONSPECT " "
            "VALUES(15, 2, 'English', 1, 'Greetings', 1, 13);";
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


/*======================= Public Methods =====================================*/

DBManager* DBManager::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new DBManager();
    }
    return mInstance;
}

void DBManager::insertRowIntoTableConspect(int id,
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
void DBManager::deleteRowFromTable(int rowId, QString tableName) {
    QString idName = QString::compare(tableName, TABLE_CONSPECT, Qt::CaseInsensitive) == 0 ?
                CONSPECT_ID : LIST_ID;
    QString deleteQuery =
            "DELETE FROM " + tableName + " "
                "WHERE " + idName  + " = " + QString::number(rowId);
    makeQuery(deleteQuery);
}
void DBManager::insertRowIntoTableList(int list_id,
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

QStandardItemModel* DBManager::getConspectModel() {
    QStandardItemModel* conspectModel = new QStandardItemModel(0, 3);

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
                        "SELECT " LIST_ID ", " CONSPECT_ID " "
                            "FROM " TABLE_CONSPECT " "
                            "WHERE " TERM " = " + QString::number(term) + " "
                            "AND " SUBJECT " = '" + subject + "' "
                            "AND " THEME " = '" + theme + "' "
                            "ORDER BY " LIST_ID_NO;
                QSqlQuery lists = makeQuery(getListId);
                QString listsCount =
                        "SELECT COUNT(" LIST_ID ") "
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
                            "SELECT " LIST_ID_NO " "
                                "FROM " TABLE_CONSPECT " "
                                "WHERE " CONSPECT_ID " = " + QString::number(id) + " ";
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
    return conspectModel;
}

QStandardItemModel* DBManager::getListModel() {
    QStandardItemModel* listModel = new QStandardItemModel(0, 1);
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
    return listModel;
}

int DBManager::findFileIdByName(QString file_name) {
    QString query =
            "SELECT " LIST_ID " "
                "FROM " TABLE_LIST " "
                "WHERE " FILE_NAME " = '" + file_name + "'";
    QSqlQuery queryResult = makeQuery(query);
    queryResult.next();
    return queryResult.value(0).toInt();
}

void DBManager::onInsertFileIntoListTable(int id, QString file_name){
    insertRowIntoTableList(id, file_name);
}

void DBManager::onInsertFileIntoListTableWithInfo(int list_id, QString file_name, QString tags, QString comments) {
    insertRowIntoTableList(list_id, file_name, tags, comments);
}

void DBManager::onRemoveFile(QString file_name){
    deleteRowFromTable(findFileIdByName(file_name), TABLE_LIST);
}

void DBManager::onInsertListIntoConspectTable(int id, int term,
                                              QString subject,
                                              int theme_no, QString theme,
                                              int list_id_no, int list_id) {
    insertRowIntoTableConspect(id, term, subject, theme_no, theme, list_id_no, list_id);
}

void DBManager::onUpdateRowInConspectTable(int id, int term,
                                           QString subject,
                                           int theme_no, QString theme,
                                           int list_id_no, int list_id) {
    insertRowIntoTableConspect(id, term, subject, theme_no, theme, list_id_no, list_id);
}

void DBManager::onDeleteRowFromConspectDB(int row_id) {
    deleteRowFromTable(row_id, TABLE_CONSPECT);
}

/* ================= Fields initialization ================= */
DBManager* DBManager::mInstance = nullptr;
