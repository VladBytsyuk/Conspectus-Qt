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
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    int row = getTermRowInModel(term);
    if (row == -1) {
        qWarning(logWarning()) << "Can't find this term: " << term;
        return false;
    }
    QModelIndex termIndex = conspectModel->index(row, 0);
    int subjects_count = termIndex.row();
    QStringList subjects;

    for (int i = 0; i < subjects_count; ++i) {
        QModelIndex index = conspectModel->index(i, 0, termIndex);
        QString subject = index.data().toString();
        subjects.push_back(subject);
    }

    QObject *boxSubject = mView->findChild<QObject*>("boxSubject");
    if (boxSubject) {
        boxSubject->setProperty("model", subjects);
        qDebug(logDebug()) << boxSubject->property("model");
    } else {
        qWarning(logWarning()) << "Can't find ComboBox";
    }

    return true;
}

int AddViewForm::getTermRowInModel(int term) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    for (int i = 0; i < conspectModel->rowCount(); ++i) {
        QModelIndex index = conspectModel->index(i, 0);
        int t = index.data().toInt();
        if (t == term) {
            return i;
        }
    }
    return -1;
}

bool AddViewForm::setThemes(QString subject) {
    return true;
}
