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
public:
    DBManager();

private:
    bool createDB();
    bool makeQuery(QString);
};

#endif // DBMANAGER_H
