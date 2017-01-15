#include <QGuiApplication>

#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtWidgets>
#include <QTreeView>
#include <QDateTime>
#include <QQmlContext>
#include "dbmanager.h"
#include "conspectmodel.h"
#include "filemanager.h"
#include "imagehandler.h"
#include "addformhandler.h"
#include "viewformhandler.h"
#include "taghandler.h"
#include "resourceimageprovider.h"
#include "utils.h"
//Log File
QFile * logFile;

//Log handler initialization
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void setSignalSlotConnections();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
    ImageHandler image_handler(engine.rootObjects().at(0)->findChild<QObject*>("showForm"));
    TagHandler tag_handler(engine.rootObjects().at(0)->findChild<QObject*>("tagForm"));

    //Open log file. Start logging
    logFile = new QFile(fm->getMainDirPath() + "/logFile.log");
    logFile->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    qDebug(logDebug()) << "Started";

    //Filling the model from the database
    ConspectModel::setConspectModel(dbManager->getConspectModel());
    ConspectModel::setListModel(dbManager->getListModel());

    conspectModel->logConspectModel();

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
    QObject::connect(conspectModel, &ConspectModel::insertListTableDBSignal,
                     dbManager, &DBManager::onInsertFileIntoListTableWithInfo);

    //BackEnd connections
    QObject::connect(&add_form, &AddFormHandler::tryToAddFileToFileSystem,
                     fm, &FileManager::onTryAddFileToFileSystem);
    QObject::connect(fm, &FileManager::invalidFilePath,
                     &add_form, &AddFormHandler::onInvalidFilePath);
    QObject::connect(fm, &FileManager::validFilePath,
                     &add_form, &AddFormHandler::onValidFilePath);
    QObject::connect(fm, &FileManager::removeFileSignal,
                     conspectModel, &ConspectModel::onRemoveFile);
    QObject::connect(&image_handler, &ImageHandler::deleteList,
                     conspectModel, &ConspectModel::onRemoveList);
    QObject::connect(&add_form, &AddFormHandler::addFileToModel,
                     conspectModel, &ConspectModel::onAddFile);
    QObject::connect(&view_form, &ViewFormHandler::changeOrder,
                     conspectModel, &ConspectModel::onChangeOrdering);
    QObject::connect(&image_handler, &ImageHandler::imageUpdated,
                     &view_form, &ViewFormHandler::onUpdateImage);
    QObject::connect(conspectModel, &ConspectModel::tryToRemoveFile,
                     fm, &FileManager::onTryToRemoveFile);
    QObject::connect(&view_form, &ViewFormHandler::setPathToList,
                     &image_handler, &ImageHandler::onSetPathToList);
    QObject::connect(&image_handler, &ImageHandler::addConspectListToAnotherPath,
                     conspectModel, &ConspectModel::onAddListToAnotherPath);
    QObject::connect(&image_handler, &ImageHandler::changeTag,
                     conspectModel, &ConspectModel::onChangeTag);
    QObject::connect(&image_handler, &ImageHandler::changeComment,
                     conspectModel, &ConspectModel::onChangeComment);
    QObject::connect(&image_handler, &ImageHandler::setViewFormIndex,
                     &view_form, &ViewFormHandler::onSetGridViewIndex);
    QObject::connect(&image_handler, &ImageHandler::setTagFormIndex,
                     &tag_handler, &TagHandler::onSetGridViewIndex);

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
                     ->findChild<QObject*>("showForm"), SIGNAL(turnedLeft(int, QString)),
                     &image_handler, SLOT(onTurnLeft(int, QString)));
    //Turn right
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(turnedRight(int, QString)),
                     &image_handler, SLOT(onTurnRight(int, QString)));
    //Print
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(printed(QString)),
                     &image_handler, SLOT(onPrint(QString)));
    //Greyscaled
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(improved(int, QString)),
                     &image_handler, SLOT(onImproveImage(int,QString)));
    //Deleted
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(deleted(QString)),
                     &image_handler, SLOT(onDelete(QString)));
    //Update ViewForm
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(updateViewForm()),
                     &view_form, SLOT(onUpdateView()));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(showFormSignal()),
                     &image_handler, SLOT(onForm()));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("boxTerm"), SIGNAL(termSelect(QString)),
                     &image_handler, SLOT(onSetTerm(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("boxSubject"), SIGNAL(subjectSelect(QString)),
                     &image_handler, SLOT(onSetSubject(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("boxTheme"), SIGNAL(themeSelect(QString)),
                     &image_handler, SLOT(onSetTheme(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("buttonSave"), SIGNAL(addList(QString)),
                     &image_handler, SLOT(onOkClicked(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("tagField"), SIGNAL(tagChanged(QString, QString)),
                     &image_handler, SLOT(onTagChanged(QString, QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm")
                     ->findChild<QObject*>("commentField"), SIGNAL(commentChanged(QString, QString)),
                     &image_handler, SLOT(onCommentChanged(QString, QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("showForm"), SIGNAL(imageSet(int, QString, QString)),
                     &image_handler, SLOT(onSetImagePath(int, QString, QString)));

    //Tag form connections
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("tagForm"), SIGNAL(search(QString)),
                     &tag_handler, SLOT(onSearchRequest(QString)));
    QObject::connect(engine.rootObjects().at(0)
                     ->findChild<QObject*>("tagForm"), SIGNAL(tagFormSignal()),
                     &tag_handler, SLOT(onForm()));

    app.exec();

    qDebug(logDebug()) << "Stoped";
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
