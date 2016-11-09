#include "filemanager.h"
#include <QDebug>

//Create project directrory in user root directory
FileManager::FileManager(){
    main_dir = QDir::home();
    if (!main_dir.cd(QString(DIR_NAME))){
        main_dir.mkdir(QString(DIR_NAME));
        main_dir.cd(QString(DIR_NAME));
    }
    main_dir_path = main_dir.path();
}

//Create project directrory in given directory
FileManager::FileManager(QString path){
    if (!main_dir.cd(path)){
        main_dir.mkpath(path);
        main_dir.cd(path);
    }
    main_dir_path = main_dir.path();
}

FileManager::~FileManager(){
	//her znaet
}

//Copy file with given name into project directory
bool FileManager::copyFile(QString file_name){
	if (!QFile(file_name).exists()){
        qDebug() << "Can't copy. File doesn't exist: " << file_name;
		return false;
	}
	QFileInfo fi(file_name);
	QString new_file_name = main_dir_path + "/" + QString::number(qrand()) + "." + fi.suffix();
	while (!QFile::copy(file_name, new_file_name)){
		new_file_name = main_dir_path + "/" + QString::number(qrand()) + "." + fi.suffix();
	}
    emit addFileSignal(QFileInfo(new_file_name).fileName());
    return true;
}

//Remove file with given name from project directory
bool FileManager::removeFile(QString file_name){
    if (!QFile(file_name).exists()){
        qDebug() << "File doesn't exist: " << file_name;
		return false;
	} 
	else if (QFileInfo(file_name).absoluteDir() != main_dir){
		qDebug() << "Wrong directory";
		return false;
	}
	else if (!QFile::remove(file_name)){
		qDebug() << "Can`t delete file";
		return false;
	} 
	else{
		emit removeFileSignal(QFileInfo(file_name).fileName());
		return true;
	}
}

//her znaet
bool FileManager::updateFile(QString file_name){
    if (!QFile(file_name).exists()){
        qDebug() << "File doesn't exist: " << file_name;
		return false;
	}
	return true;
}

//Get QImage object from project directory
QImage FileManager::getImage(QString file_name){
	QImage img;
	if (!img.load(file_name)){
		qDebug() << "Can't load this file: " << file_name;
		return QImage();
	}
	else if (QFileInfo(file_name).absoluteDir() != main_dir){
		qDebug() << "Wrong directory";
		return QImage();
	}
	else{
		return img;
	}
}

QString FileManager::getMainDirPath(){
	return main_dir_path;
}

