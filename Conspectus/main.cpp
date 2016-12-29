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
#include "imagehandler.h"
#include "addformhandler.h"
#include "viewformhandler.h"
#include "resourceimageprovider.h"
#include "utils.h"
//Log File
QFile * logFile;

//Log handler initialization
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void setSignalSlotConnections();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Util util;
    QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));
    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("sourceDir"), new ResourceImageProvider(QQuickImageProvider::Pixmap));
    engine.rootContext()->setContextProperty("utils", &util);
    engine.load(qmlUrl);

	FileManager * fm = new FileManager();
    DBManager* dbManager = DBManager::getInstance();
    ConspectModel* conspectModel = ConspectModel::getInstance();
    AddFormHandler add_form(engine.rootObjects().at(0)->findChild<QObject*>("addForm"));
    ViewFormHandler view_form(engine.rootObjects().at(0)->findChild<QObject*>("viewForm"));
    ImageHandler * image_handler = new ImageHandler(engine.rootObjects().at(0)->findChild<QObject*>("showForm"));

    //Open log file. Start logging
    logFile = new QFile(fm->getMainDirPath() + "/logFile.log");
    logFile->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    qDebug(logDebug()) << "Started";

    //Filling the model from the database
    ConspectModel::setConspectModel(dbManager->getConspectModel());
    ConspectModel::setListModel(dbManager->getListModel());

    setSignalSlotConnections();

    //Model <--> DB connections
    QObject::connect(conspectModel, &ConspectModel::insertFileDBSignal,
                     dbManager, &DBManager::onInsertFileIntoListTable);
    QObject::connect(conspectModel, &ConspectModel::removeFileDBSignal,
                     dbManager, &DBManager::onRemoveFile);
    QObject::connect(conspectModel, &ConspectModel::insertListDBSignal,
                     dbManager, &DBManager::onInsertListIntoConspectTable);
    QObject::connect(conspectModel, &ConspectModel::updateRowInConspectTable,
                     dbManager, &DBManager::onUpdateRowInConspectTable);
    QObject::connect(conspectModel, &ConspectModel::removeRowFromConspectDB,
                     dbManager, &DBManager::onDeleteRowFromConspectDB);

    //BackEnd connections
    QObject::connect(&add_form, &AddFormHandler::tryToAddFileToFileSystem,
                     fm, &FileManager::onTryAddFileToFileSystem);
    QObject::connect(fm, &FileManager::invalidFilePath,
                     &add_form, &AddFormHandler::onInvalidFilePath);
    QObject::connect(fm, &FileManager::validFilePath,
                     &add_form, &AddFormHandler::onValidFilePath);
    QObject::connect(fm, &FileManager::removeFileSignal,
                     conspectModel, &ConspectModel::onRemoveFile);
    QObject::connect(image_handler, &ImageHandler::deleteList,
                     conspectModel, &ConspectModel::onRemoveList);
    QObject::connect(&add_form, &AddFormHandler::addFileToModel,
                     conspectModel, &ConspectModel::onAddFile);
    QObject::connect(&view_form, &ViewFormHandler::changeOrder,
                     conspectModel, &ConspectModel::onChangeOrdering);
    QObject::connect(image_handler, &ImageHandler::imageUpdated,
                     &view_form, &ViewFormHandler::onUpdateImage);
    QObject::connect(conspectModel, &ConspectModel::tryToRemoveFile,
                     fm, &FileManager::onTryToRemoveFile);
    QObject::connect(&view_form, &ViewFormHandler::setPathToList,
                     image_handler, &ImageHandler::onSetPathToList);

    //ViewForm connections
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm"), SIGNAL(viewFormSignal()),
                     &view_form, SLOT(onForm()));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm")
                     ->findChild<QObject*>("boxTerm"), SIGNAL(termSelect(QString)),
                     &view_form, SLOT(onSetTerm(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm")
                     ->findChild<QObject*>("boxSubject"), SIGNAL(subjectSelect(QString)),
                     &view_form, SLOT(onSetSubject(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm")
                     ->findChild<QObject*>("boxTheme"), SIGNAL(themeSelect(QString)),
                     &view_form, SLOT(onSetTheme(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm")
                     ->findChild<QObject*>("gridView"), SIGNAL(orderChanged(int, int)),
                     &view_form, SLOT(onOrderChanged(int,int)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("viewForm")
                     ->findChild<QObject*>("gridView"), SIGNAL(setPath()),
                     &view_form, SLOT(onSetPath()));

    //AddForm connections
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("addForm"), SIGNAL(addFormSignal()),
                     &add_form, SLOT(onForm()));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("addForm")
                     ->findChild<QObject*>("boxTerm"), SIGNAL(termSelect(QString)),
                     &add_form, SLOT(onSetTerm(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("addForm")
                     ->findChild<QObject*>("boxSubject"), SIGNAL(subjectSelect(QString)),
                     &add_form, SLOT(onSetSubject(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("addForm")
                     ->findChild<QObject*>("boxTheme"), SIGNAL(themeSelect(QString)),
                     &add_form, SLOT(onSetTheme(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("addForm")
                     ->findChild<QObject*>("buttonOk"), SIGNAL(okClicked(QString)),
                     &add_form, SLOT(onOkClicked(QString)));

    //ShowForm connections
    //Turn left
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(turnedLeft(QString)),
                     image_handler, SLOT(onTurnLeft(QString)));
    //Turn right
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(turnedRight(QString)),
                     image_handler, SLOT(onTurnRight(QString)));
    //Print
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(printed(QString)),
                     image_handler, SLOT(onPrint(QString)));
    //Greyscaled
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(greyscaled(QString)),
                     image_handler, SLOT(onGreyscale(QString)));
    //Deleted
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(deleted(QString)),
                     image_handler, SLOT(onDelete(QString)));
    app.exec();

    qDebug(logDebug()) << "Stoped";
    delete image_handler;
	delete fm;
	delete dbManager;
	delete logFile;


    return 0;
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
