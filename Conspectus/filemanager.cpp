#include "filemanager.h"
#include "loggingcategories.h"
#include <QDebug>

//Create project directrory in user root directory
FileManager::FileManager(){
    main_dir = QDir::home();
	if (!main_dir.cd(QString(MAIN_DIR_NAME))){
		main_dir.mkdir(QString(MAIN_DIR_NAME));
		main_dir.cd(QString(MAIN_DIR_NAME));
    }
	source_dir = main_dir;
	if (!source_dir.cd(QString(SOURCE_DIR_NAME))){
		source_dir.mkdir(QString(SOURCE_DIR_NAME));
		source_dir.cd(QString(SOURCE_DIR_NAME));
	}
    preview_dir = source_dir;
    if (!preview_dir.cd(QString(PREVIEW_NAME))) {
        preview_dir.mkdir(QString(PREVIEW_NAME));
        preview_dir.cd(QString(PREVIEW_NAME));
    }
    main_dir_path = main_dir.path();
	source_dir_path = source_dir.path();
    preview_dir_path = preview_dir.path();
}

//Create project directrory in given directory
FileManager::FileManager(QString path){
	main_dir = QDir::root();
	QString new_path = path + "/" + MAIN_DIR_NAME;
	if (!main_dir.cd(new_path)){
		main_dir.mkpath(new_path);
		main_dir.cd(new_path);
    }
	source_dir = main_dir;
	if (!source_dir.cd(QString(SOURCE_DIR_NAME))){
		source_dir.mkdir(QString(SOURCE_DIR_NAME));
        source_dir.cd(QString(SOURCE_DIR_NAME));
	}
    preview_dir = source_dir;
    if (!preview_dir.cd(QString(PREVIEW_NAME))) {
        preview_dir.mkdir(QString(PREVIEW_NAME));
        preview_dir.cd(QString(PREVIEW_NAME));
    }
    main_dir_path = main_dir.path();
	source_dir_path = main_dir.path();
    preview_dir_path = preview_dir.path();
}

FileManager::~FileManager(){
}

//Copy file with given name into project directory
QString FileManager::copyFile(QString file_name){
	if (!QFile(file_name).exists()){
		qCritical(logCritical()) << "Can't copy file. File doesn't exists: " << file_name;
        return QString();
	}
	QFileInfo fi(file_name);
    QString short_file_name = QString::number(qrand()) + "." + fi.suffix();
    QString new_file_name = source_dir_path + "/" + short_file_name;
    while (!QFile::copy(file_name, new_file_name)){
        short_file_name = QString::number(qrand()) + "." + fi.suffix();
        new_file_name = source_dir_path + "/" + short_file_name;
	}

    QString preview_file_name = source_dir_path + "/" + PREVIEW_NAME + "/" + short_file_name;
    QImage image(file_name);
    image = image.scaledToWidth(480);
    image.save(preview_file_name, 0, 80);

	qDebug(logDebug()) << "File " + QFileInfo(file_name).fileName() + " has been copied into project`s directory";
    return new_file_name;
}

//Remove file with given name from project directory
bool FileManager::removeFile(QString file_name){
    QString absolute_file_name = getImagePath(file_name);
    if (!QFile(absolute_file_name).exists()){
		qCritical(logCritical()) << "Can`t delete file. File doesn't exist: " << file_name;
		return false;
	} 
    else if (QFileInfo(absolute_file_name).absoluteDir() != source_dir){
		qCritical(logCritical()) << "Wrong directory. Access denied";
		return false;
	}
    else if (!QFile::remove(absolute_file_name)){
		qCritical(logCritical()) << "Can`t delete file";
		return false;
	} 
    else if (!QFile::remove(getImagePreviewPath(file_name))) {
        qCritical(logCritical()) << "Can't delete preview";
        return false;
    }
	else{
        qDebug(logDebug()) << "File " + QFileInfo(absolute_file_name).fileName() + " has been removed from project`s directory";
		emit removeFileSignal(QFileInfo(file_name).fileName());
		return true;
	}
}

//Get QImage preview object from project`s direvtory
QImage FileManager::getImage(QString file_name){
    QImage img;
    if (!img.load(getImagePath(file_name))){
        qCritical(logCritical()) << "Can't load this image: " << file_name;
        return QImage();
    } else {
        return img;
    }
}

//Get QImage preview object from project`s direvtory
QImage FileManager::getImagePreview(QString file_name) {
    QImage img;
    if (!img.load(getImagePreviewPath(file_name))){
        qCritical(logCritical()) << "Can't load this preview image: " << file_name;
        return QImage();
    } else {
        return img;
    }
}

//Get QPixmap object from project`s directory
QPixmap FileManager::getPixmap(QString file_name){
    QPixmap img;
    if (!img.load(getImagePath(file_name))){
        qCritical(logCritical()) << "Can't load this image: " << file_name;
        return QPixmap();
    } else {
		return img;
	}
}

//Get QPixmap preview object from project`s direvtory
QPixmap FileManager::getPixmapPreview(QString file_name) {
    QPixmap img;
    if (!img.load(getImagePreviewPath(file_name))){
        qCritical(logCritical()) << "Can't load this preview image: " << file_name;
        return QPixmap();
    } else {
        return img;
    }
}

//Get image absolute path
QString FileManager::getImagePath(QString file_name) {
    return source_dir_path + "/" + file_name;
}

//Get image preview absolute path
QString FileManager::getImagePreviewPath(QString file_name) {
    return preview_dir_path + "/" + file_name;
}

//Get project`s directory
QString FileManager::getMainDirPath(){
	return main_dir_path;
}

//Get project`s source directory
QString FileManager::getSourceDirPath(){
	return source_dir_path;
}

//Get source preview directory
QString FileManager::getPreviewDirPath() {
    return preview_dir_path;
}

void FileManager::onTryAddFileToFileSystem(QString file_path) {
    QString new_file_name = copyFile(file_path);
    if (new_file_name.isNull()){
        qCritical(logCritical()) << "Invalid file path: " << file_path;
        emit invalidFilePath();
    } else {
        emit validFilePath(QFileInfo(new_file_name).fileName());
    }
}

void FileManager::onTryToRemoveFile(QString file_name) {
    removeFile(file_name);
}
