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
    main_dir_path = main_dir.path();
	source_dir_path = source_dir.path();
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
    main_dir_path = main_dir.path();
	source_dir_path = main_dir.path();
}

FileManager::~FileManager(){
}

//Copy file with given name into project directory
bool FileManager::copyFile(QString file_name){
	if (!QFile(file_name).exists()){
		qCritical(logCritical()) << "Can't copy file. File doesn't exists: " << file_name;
		return false;
	}
	QFileInfo fi(file_name);
	QString new_file_name = source_dir_path + "/" + QString::number(qrand()) + "." + fi.suffix();
	while (!QFile::copy(file_name, new_file_name)){
		new_file_name = source_dir_path + "/" + QString::number(qrand()) + "." + fi.suffix();
	}
	qDebug(logDebug()) << "File " + QFileInfo(file_name).fileName() + " has been copied into project`s directory";
    emit addFileSignal(QFileInfo(new_file_name).fileName());
    return true;
}

//Remove file with given name from project directory
bool FileManager::removeFile(QString file_name){
    if (!QFile(file_name).exists()){
		qCritical(logCritical()) << "Can`t delete file. File doesn't exist: " << file_name;
		return false;
	} 
	else if (QFileInfo(file_name).absoluteDir() != source_dir){
		qCritical(logCritical()) << "Wrong directory. Access denied";
		return false;
	}
	else if (!QFile::remove(file_name)){
		qCritical(logCritical()) << "Can`t delete file";
		return false;
	} 
	else{
		qDebug(logDebug()) << "File " + QFileInfo(file_name).fileName() + " has been removed from project`s directory";
		emit removeFileSignal(QFileInfo(file_name).fileName());
		return true;
	}
}

//her znaet
bool FileManager::updateFile(QString file_name){
    if (!QFile(file_name).exists()){
		qCritical(logCritical()) << "File doesn't exist: " << file_name;
		return false;
	}
	return true;
}

//Get QImage object from project directory
QImage FileManager::getImage(QString file_name){
	QImage img;
	if (!img.load(file_name)){
		qCritical(logCritical()) << "Can't load this image: " << file_name << ". Its format probably wrong";
		return QImage();
	}
	else if (QFileInfo(file_name).absoluteDir() != source_dir){
		qCritical(logCritical()) << "Wrong directory. Access denied";
		return QImage();
	}
	else{
		return img;
	}
}

QString FileManager::getMainDirPath(){
	return main_dir_path;
}

QString FileManager::getSourceDirPath(){
	return source_dir_path;
}