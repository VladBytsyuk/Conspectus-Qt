#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QScopedPointer>

#define MAIN_DIR_NAME "Conspectus"
#define SOURCE_DIR_NAME "Source"

class FileManager: public QObject{
    Q_OBJECT
private:
    /* ==================== Constructor ==================== */

    /* ====================== Fields ======================= */
    QDir main_dir;
    QString main_dir_path;
	QDir source_dir;
	QString source_dir_path;

    /* ====================== Methods ====================== */
    QString randomNameGenerator(QString path);

public:
        /* ==================== Constructor ==================== */
    FileManager();
    FileManager(QString path);
    ~FileManager();
        /* ====================== Fields ======================= */

        /* ====================== Methods ====================== */
    QString copyFile(QString file_name);
    bool removeFile(QString path);
    bool updateFile(QString path);
    QImage getImage(QString path);
	QString getMainDirPath();
	QString getSourceDirPath();
	QScopedPointer<QFile> getLogFile();

signals:
    void addFileSignal(QString file_name);
    void removeFileSignal(QString file_name);
    void invalidFilePath();
    void validFilePath(QString file_name);

public slots:
    void onTryAddFileToFileSystem(QString file_path);
};

#endif // FILEMANAGER_H
