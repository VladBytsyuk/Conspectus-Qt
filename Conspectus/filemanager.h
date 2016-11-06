#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>

#define DIR_NAME "Conspectus_source"

class FileManager: public QObject{
private:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */
    QDir main_dir;
    QString main_dir_path;
    /* ====================== Methods ====================== */
    QString randomNameGenerator(QString path);

public:
        /* ==================== Constructor ==================== */
    FileManager();
    FileManager(QString path);
    ~FileManager();
        /* ====================== Fields ======================= */

        /* ====================== Methods ====================== */
    bool copyFile(QString file_name);
    bool removeFile(QString path);
    bool updateFile(QString path);
    QImage getImage(QString path);
};

#endif // FILEMANAGER_H
