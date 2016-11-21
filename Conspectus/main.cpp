#include <QGuiApplication>

#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTreeView>
#include <QDateTime>
#include <QQmlContext>
#include "dbmanager.h"
#include "conspectmodel.h"
#include "filemanager.h"
#include "advancedimage.h"
#include "addviewform.h"

//Log File
QFile * logFile;

//Log handler initialization
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void setSignalSlotConnections();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));
    QQmlApplicationEngine engine;
    engine.load(qmlUrl);

	FileManager * fm = new FileManager();

    //open log file. Start logging
    logFile = new QFile(fm->getMainDirPath() + "/logFile.log");
    logFile->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    qDebug(logDebug()) << "Started";


    DBManager* dbManager = DBManager::getInstance();
    ConspectModel* conspectModel = ConspectModel::getInstance();
    ConspectModel::setConspectModel(dbManager->getConspectModel());
    ConspectModel::setListModel(dbManager->getListModel());


    //TODO: Implement this method.
    //(Maybe FileManager should be singleton? Because we need same object inside this method77)
    setSignalSlotConnections();
    QObject::connect(fm, &FileManager::addFileSignal, conspectModel, &ConspectModel::onInsertFile);
    QObject::connect(fm, &FileManager::removeFileSignal, conspectModel, &ConspectModel::onRemoveFile);

    QObject::connect(conspectModel, &ConspectModel::insertFileDBSignal, dbManager, &DBManager::onInsertFile);
    QObject::connect(conspectModel, &ConspectModel::removeFileDBSignal, dbManager, &DBManager::onRemoveFile);

    QString temp = fm->getSourceDirPath() + "/1661.bmp";
	fm->copyFile(temp);
    fm->removeFile(temp);

    AddViewForm add_from(engine.rootObjects().at(0)->findChild<QObject*>("addForm"));
    add_from.setTerms();
    add_from.setSubjects(2);

	qDebug(logDebug()) << "Stoped"; 
    /*
	delete fm;
	delete dbManager;
	delete logFile;
    */
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

void setSignalSlotConnections() {

}
