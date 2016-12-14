#include "viewformhandler.h"

ViewFormHandler::ViewFormHandler(QObject* view) {
    mView = view;
}

ViewFormHandler::~ViewFormHandler() {}

void ViewFormHandler::onOkClicked(QString file_path) {

}

QStringList ViewFormHandler::getImageSources(int term, QString subject, QString theme) {
    QList<int> listIds = getListIds(term, subject, theme);
    return getFileNames(listIds);
}

QList<int> ViewFormHandler::getListIds(int term, QString subject, QString theme) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    QList<int> ids;

    int terms_count = conspectModel->rowCount();
    for (int termIterator = 0; termIterator < terms_count; ++termIterator) {
        QModelIndex termIndex = conspectModel->index(termIterator, 0);
        int current_term = termIndex.data().toInt();
        if (current_term == term) {
            int subjects_count = conspectModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
                QModelIndex subjectIndex = conspectModel->index(subjectIterator, 0, termIndex);
                QString current_subject = subjectIndex.data().toString();
                if (current_subject == subject) {
                    int themes_count = conspectModel->rowCount(subjectIndex);
                    for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                        QModelIndex themeIndex = conspectModel->index(themeIterator, 0, subjectIndex);
                        QString current_theme = themeIndex.data().toString();
                        if (current_theme == theme) {
                            int lists_count = conspectModel->rowCount(themeIndex);
                            for (int listIterator = 0; listIterator < lists_count; ++ listIterator) {
                                QModelIndex listIndex = conspectModel->index(listIterator, 0, themeIndex);
                                int current_list_id = listIndex.data().toInt();
                                ids.push_back(current_list_id);
                            }
                            return ids;
                        }
                    }
                }
            }
        }
    }
}

QStringList ViewFormHandler::getFileNames(const QList<int> &listIds) {
    QStandardItemModel* listModel = ConspectModel::getListModel();
    QStringList fileSources;
    int row_count = listModel->rowCount();
    for (int i = 0; i < row_count; ++i) {
        QModelIndex index = listModel->index(i, 0);
        int id = index.data().toInt();
        if (listIds.contains(id)) {
            QModelIndex fileSourceIndex = listModel->index(i, 1);
            fileSources.push_back(fileSourceIndex.data().toString());
        }
    }
    return fileSources;
}

bool ViewFormHandler::invokeSetImages() {
    QStringList list = getImageSources(mCurrentTerm, mCurrentSubject, mCurrentTheme);
    return true;
}

void ViewFormHandler::onSetTheme(QString theme) {
    FormHandler::onSetTheme(theme);
    this->invokeSetImages();
}
