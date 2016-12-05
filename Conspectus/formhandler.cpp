#include "formhandler.h"

bool FormHandler::setTerms() {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    int terms_count = conspectModel->rowCount();
    if (terms_count == 0) {
        qDebug(logDebug()) << "Terms count = 0";
        return false;
    }
    QStringList terms;
    for (int i = 0; i < terms_count; ++i) {
        QModelIndex index = conspectModel->index(i, 0);
        int term = index.data().toInt();
        terms.push_back(QString::number(term));
    }

    QObject *boxTerm = mView->findChild<QObject*>("boxTerm");
    if (boxTerm) {
        boxTerm->setProperty("model", terms);
    } else {
        qWarning(logWarning()) << "Can't find ComboBox boxTerm";
        return false;
    }
    return true;
}

bool FormHandler::setSubjects(int term) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    int row = getTermRowInModel(term);
    if (row == -1) {
        qWarning(logWarning()) << "Can't find this term: " << term;
        return false;
    }
    QModelIndex termIndex = conspectModel->index(row, 0);
    int subjects_count = conspectModel->rowCount(termIndex);
    if (subjects_count == 0) {
        qDebug(logDebug()) << "Subjects count = 0";
        return false;
    }

    QStringList subjects;
    for (int i = 0; i < subjects_count; ++i) {
        QModelIndex index = conspectModel->index(i, 0, termIndex);
        QString subject = index.data().toString();
        subjects.push_back(subject);
    }

    QObject *boxSubject = mView->findChild<QObject*>("boxSubject");
    if (boxSubject) {
        boxSubject->setProperty("model", subjects);
    } else {
        qWarning(logWarning()) << "Can't find ComboBox boxSubject";
        return false;
    }

    return true;
}

int FormHandler::getTermRowInModel(int term) {
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

bool FormHandler::setThemes(int term, QString subject) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    int termRow = getTermRowInModel(term);
    if (termRow == -1) {
        qWarning(logWarning()) << "Can't find this term: " << term;
        return false;
    }
    int subjectRow = getSubjectRowInModel(termRow, subject);
    if (termRow == -1) {
        qWarning(logWarning()) << "Can't find this subject: " << subject;
        return false;
    }
    QModelIndex termIndex = conspectModel->index(termRow, 0);
    QModelIndex subjectIndex = conspectModel->index(subjectRow, 0, termIndex);
    int themes_count = conspectModel->rowCount(subjectIndex);
    if (themes_count == 0) {
        qDebug(logDebug()) << "Themes count = 0";
        return false;
    }

    QStringList themes;
    for (int i = 0; i < themes_count; ++i) {
        QModelIndex index = conspectModel->index(i, 0, subjectIndex);
        QString theme = index.data().toString();
        themes.push_back(theme);
    }

    QObject *boxTheme = mView->findChild<QObject*>("boxTheme");
    if (boxTheme) {
        boxTheme->setProperty("model", themes);
    } else {
        qWarning(logWarning()) << "Can't find ComboBox boxTheme";
        return false;
    }

    return true;
}

int FormHandler::getSubjectRowInModel(int term_row, QString subject) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    QModelIndex termIndex = conspectModel->index(term_row, 0);
    for (int i = 0; i < conspectModel->rowCount(termIndex); ++i) {
        QModelIndex index = conspectModel->index(i, 0, termIndex);
        QString subj = index.data().toString();
        if (subj == subject) {
            return i;
        }
    }
    return -1;
}

void FormHandler::onSetTerm(QString term) {
    mCurrentTerm = term.toInt();
    this->setSubjects(mCurrentTerm);
}

void FormHandler::onSetSubject(QString subject) {
    mCurrentSubject = subject;
    this->setThemes(mCurrentTerm, mCurrentSubject);
}


void FormHandler::onSetTheme(QString theme) {
    mCurrentTheme = theme;
}

void FormHandler::onForm() {
    this->setTerms();
}
