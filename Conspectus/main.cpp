#include <QApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQuickView>
#include <QTreeView>
#include <QTime>
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));

    QQmlApplicationEngine engine;
    engine.load(qmlUrl);

    DBManager* dbManager = DBManager::getInstance();

    QTreeView tree;
    dbManager->getModel();
    tree.setModel(ConspectModel::getConspectModel());
    tree.show();  

    QTreeView tree1;
    tree1.setModel(ConspectModel::getListModel());
    tree1.show();

	FileManager * fm = new FileManager();
    QString temp = "~/test.bmp";
	fm->copyFile(temp);
	fm->removeFile(temp);
	QImage img = fm->getImage(temp);

    return app.exec();
}
