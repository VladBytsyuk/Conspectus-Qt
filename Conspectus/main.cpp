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

//    QStandardItemModel model(200,1);
//    for (int i = 0; i < 200; i++) {
//        QModelIndex index = model.index(i, 0);
//        model.setData(index, i);

//        model.insertRows(0, 2, index);
//        model.insertColumns(0, 1, index);
//        for (int k = 0; k < 2; k++) {
//            model.setData(model.index(k, 0, index), "exit");
//        }
//    }
    
//    QTreeView t;
//    t.setModel(&model);
//    t.show();

    ConspectModel* myModel = dbManager->getConspectModel();

    return app.exec();
}
