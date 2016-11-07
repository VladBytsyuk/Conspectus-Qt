#include <QApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQuickView>
#include <QTreeView>
#include <QTime>
#include "dbmanager.h"
#include "imagemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    
	QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));
	QQmlApplicationEngine engine;
	engine.load(qmlUrl);

	FileManager * fm = new FileManager();
	DBManager* dbManager = DBManager::getInstance();

	QObject::connect(fm, &FileManager::addFileSignal, dbManager, &DBManager::onAddFile);
	QObject::connect(fm, &FileManager::removeFileSignal, dbManager, &DBManager::onRemoveFile);

	//QString temp = "~/test.bmp";
	QString temp = fm->getMainDirPath() + "/21146.bmp";
	//QString temp = "J:/temp.bmp";
	//fm->copyFile(temp);
	//fm->removeFile(temp);

    QTreeView tree;
    dbManager->getModel();
    tree.setModel(ConspectModel::getConspectModel());
    tree.show();  

    QTreeView tree1;
    tree1.setModel(ConspectModel::getListModel());
    tree1.show();

	ImageManager im(&(fm->getImage(temp)));

	delete fm;
	delete dbManager;
    return app.exec();
}
