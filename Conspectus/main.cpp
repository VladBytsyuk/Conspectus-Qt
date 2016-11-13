#include <QApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTreeView>
#include <QDateTime>
#include "dbmanager.h"
#include "conspectmodel.h"
#include "filemanager.h"
#include "advancedimage.h"

//Log File
QFile * logFile;

//Log handler initialization
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));
	QQmlApplicationEngine engine;
	engine.load(qmlUrl);

	FileManager * fm = new FileManager();
	DBManager* dbManager = DBManager::getInstance();
    ConspectModel* conspectModel = ConspectModel::getInstance();
    ConspectModel::setConspectModel(dbManager->getConspectModel());
    ConspectModel::setListModel(dbManager->getListModel());

	//open log file. Start logging
	logFile = new QFile(fm->getMainDirPath() + "/logFile.log");
	logFile->open(QFile::Append | QFile::Text);
	qInstallMessageHandler(messageHandler);

	qDebug(logDebug()) << "Started";

    //QObject::connect(fm, &FileManager::addFileSignal, dbManager, &DBManager::onAddFile);
    //QObject::connect(fm, &FileManager::removeFileSignal, dbManager, &DBManager::onRemoveFile);

    QObject::connect(fm, &FileManager::addFileSignal, conspectModel, &ConspectModel::onInsertFile);
    QObject::connect(fm, &FileManager::removeFileSignal, conspectModel, &ConspectModel::onRemoveFile);

    //QString temp = "~/test.bmp";
    QString temp = fm->getSourceDirPath() + "/1661.bmp";
	//QString temp = "J:/temp.bmp";
	fm->copyFile(temp);
    //fm->removeFile(temp);

    QTreeView tree;
    tree.setModel(ConspectModel::getConspectModel());
    tree.show();  

    QTreeView tree1;
    tree1.setModel(ConspectModel::getListModel());
    tree1.show();

//	AdvancedImage im(&(fm->getImage(temp)));
	qDebug(logDebug()) << "Stoped"; 

	delete fm;
	delete dbManager;
	delete logFile;
    return app.exec();
}

//Logging handler
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QTextStream out(logFile);

	out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

	switch (type){
	case QtInfoMsg:     out << "INF "; break;
	case QtDebugMsg:    out << "DBG "; break;
	case QtWarningMsg:  out << "WRN "; break;
	case QtCriticalMsg: out << "CRT "; break;
	case QtFatalMsg:    out << "FTL "; break;
	}

	out << msg << endl;
	out.flush();
}
