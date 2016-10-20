#include <QApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQuickView>
#include <QTreeView>
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QUrl qmlUrl = QUrl(QStringLiteral("qrc:/main.qml"));

    QQmlApplicationEngine engine;
    engine.load(qmlUrl);

    DBManager* dbManager = DBManager::getInstance();

    QTreeView tree;
    dbManager->getModel();
    tree.setModel(ConspectModel::getConspectModel());
    tree.show();

//    QTreeView tree1;
//    tree1.setModel(ConspectModel::getListModel());
//    tree1.show();

    return app.exec();
}
