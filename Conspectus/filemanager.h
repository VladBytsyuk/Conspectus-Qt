#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QFileInfo>
#include <QScopedPointer>

#define MAIN_DIR_NAME "Conspectus"
#define SOURCE_DIR_NAME "Source"
#define PREVIEW_NAME "Preview"

class FileManager: public QObject{
    Q_OBJECT
private:
    QDir main_dir;
    QString main_dir_path;
	QDir source_dir;
	QString source_dir_path;
    QDir preview_dir;
    QString preview_dir_path;

    QString randomNameGenerator(QString path);

public:
    FileManager();
    FileManager(QString path);
    ~FileManager();

    QString copyFile(QString file_name);
    bool removeFile(QString path);

    QImage getImage(QString file_name);
    QImage getImagePreview(QString file_name);
    QPixmap getPixmap(QString file_name);
    QPixmap getPixmapPreview(QString file_name);

    QString getImagePath(QString file_name);
    QString getImagePreviewPath(QString file_name);
    QString getMainDirPath();
    QString getSourceDirPath();
    QString getPreviewDirPath();

    QScopedPointer<QFile> getLogFile();

signals:
    void addFileSignal(QString file_name);
    void removeFileSignal(QString file_name);
    void invalidFilePath();
    void validFilePath(QString file_name);

public slots:
    void onTryAddFileToFileSystem(QString file_path);
    void onTryToRemoveFile(QString file_name);
};

#endif // FILEMANAGER_H
