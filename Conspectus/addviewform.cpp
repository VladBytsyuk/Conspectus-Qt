#include "addviewform.h"

AddViewForm::AddViewForm(QObject* view)
{
    mView = view;
}

bool AddViewForm::setTerms() {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    int terms_count = conspectModel->rowCount();
    QStringList terms;
    for (int i = 0; i < terms_count; ++i) {
        QModelIndex index = conspectModel->index(i, 0);
        int term = index.data().toInt();
        terms.push_back(QString::number(term));
    }
//    QQuickView view;
//    view.setSource(QStringLiteral("qrc:/AddForm.qml"));
//    view.show();

    QObject *boxTerm = mView->findChild<QObject*>("boxTerm");
    if (boxTerm) {
        boxTerm->setProperty("model", terms);
        qDebug(logDebug()) << boxTerm->property("model");
    } else {
        qWarning(logWarning()) << "Can't find ComboBox";
    }
    return true;
}

bool AddViewForm::setSubjects(int term) {
    return true;
}

bool AddViewForm::setThemes(QString subject) {
    return true;
}
