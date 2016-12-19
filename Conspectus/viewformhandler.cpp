#include "viewformhandler.h"

ViewFormHandler::ViewFormHandler(QObject* view) {
    mView = view;
}

ViewFormHandler::~ViewFormHandler() {}

void ViewFormHandler::onOkClicked(QString file_path) {

}

QStringList ViewFormHandler::getImageSources(int term, QString subject, QString theme, QList<int> *list_nos) {
    QList<int> listIds = getListIds(term, subject, theme, list_nos);
    return getFileNames(listIds);
}

QList<int> ViewFormHandler::getListIds(int term, QString subject, QString theme, QList<int> *list_nos) {
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
                                QModelIndex listNoIndex = conspectModel->index(listIterator, 1, themeIndex);
                                int list_no = listNoIndex.data().toInt();
                                list_nos->push_back(list_no);
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

void ViewFormHandler::setImageToQml(QString file_name, int list_no) {
    QObject *listModel = mView->findChild<QObject*>("photoBar");//->findChild<QObject*>("listModel");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "onSetImageToQml", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, file_name), Q_ARG(QVariant, list_no));
}

void ViewFormHandler::clearViewsFromView() {
    QObject *listModel = mView->findChild<QObject*>("photoBar");//->findChild<QObject*>("listModel");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "clearView", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, empty));
}

bool ViewFormHandler::invokeSetImages() {
    QList<int> list_nos;
    QStringList list = getImageSources(mCurrentTerm, mCurrentSubject, mCurrentTheme, &list_nos);
    clearViewsFromView();
    QMap<int, QString> images;
    for (int i = 0; i < list.size(); ++i) {
        images[list_nos[i]] = list.at(i);
    }
    qSort(list_nos);
    for (auto it = list_nos.begin(); it != list_nos.end(); ++it) {
        setImageToQml(images[*it], *it);
    }
    return true;
}

void ViewFormHandler::onSetTheme(QString theme) {
    FormHandler::onSetTheme(theme);
    this->invokeSetImages();
}

void ViewFormHandler::changeModelOrdering(int previous_index, int current_index) {
    emit changeOrder(mCurrentTerm, mCurrentSubject, mCurrentTheme, previous_index, current_index);
}

void ViewFormHandler::reloadGridView() {
    this->invokeSetImages();
}

void ViewFormHandler::onOrderChanged(int previous_index, int current_index) {
    changeModelOrdering(previous_index, current_index);
    reloadGridView();
}
