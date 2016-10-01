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

    QStandardItemModel model(2,3);
    for (int row = 0; row < 2; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item =
                    new QStandardItem(QString("row %0, column %1")
                                      .arg(row)
                                      .arg(column));
            model.setItem(row, column, item);
        }
    }

    QTreeView t;
    t.setModel(&model);
    t.show();

    return app.exec();
}
