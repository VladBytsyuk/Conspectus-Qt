#include "viewformhandler.h"

ViewFormHandler::ViewFormHandler(QObject* view) {
    mView = view;
    forcedUpdateSubject = false;
    forcedUpdateTheme = false;
}

ViewFormHandler::~ViewFormHandler() {}

void ViewFormHandler::onOkClicked(QString file_path) {

}

QMap<int, QString> ViewFormHandler::getImageSources(int term, QString subject, QString theme) {
    QMap<int, QString> images = getListIds(term, subject, theme);
    return getFileNames(images);
}

QMap<int, QString> ViewFormHandler::getListIds(int term, QString subject, QString theme) {
    QStandardItemModel* conspectModel = ConspectModel::getConspectModel();
    QMap<int, QString> images;
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
                                QModelIndex listNoIndex = conspectModel->index(listIterator, 1, themeIndex);
                                int list_no = listNoIndex.data().toInt();
                                images[list_no] = QString::number(current_list_id);
                            }
                            return images;
                        }
                    }
                }
            }
        }
    }
}

QMap<int, QString> ViewFormHandler::getFileNames(QMap<int, QString> &images) {
    for (auto it = images.begin(); it != images.end(); ++it) {
        images[it.key()] = getNameById(it.value().toInt());
    }
    return images;
}

QString ViewFormHandler::getNameById(int list_id) {
    QStandardItemModel* model = ConspectModel::getListModel();
    int row_count = model->rowCount();
    for (int i = 0; i < row_count; ++i) {
        QModelIndex idIndex = model->index(i, 0);
        if (idIndex.data().toInt() == list_id) {
            QModelIndex nameIndex = model->index(i, 1);
            return nameIndex.data().toString();
        }
    }
    return "";
}

void ViewFormHandler::setImageToQml(QString file_name, int list_no) {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "onSetImageToQml", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, file_name), Q_ARG(QVariant, list_no));
}

void ViewFormHandler::clearViewsFromView() {
    QObject *listModel = mView->findChild<QObject*>("photoBar");
    QVariant empty;
    QMetaObject::invokeMethod(listModel, "clearView", Q_RETURN_ARG(QVariant, empty),
                              Q_ARG(QVariant, empty));
}

bool ViewFormHandler::invokeSetImages() {
    QMap<int, QString> images = getImageSources(mCurrentTerm, mCurrentSubject, mCurrentTheme);
    QList<int> listNos;
    for (auto it = images.begin(); it != images.end(); ++it) {
        listNos.push_back(it.key());
    }
    qSort(listNos);
    int number = 1;
    for (auto it = listNos.begin(); it != listNos.end(); ++it) {
        setImageToQml(images[*it], number++);
    }
    return true;
}

void ViewFormHandler::onSetTheme(QString theme) {
    FormHandler::onSetTheme(theme);
    reloadGridView();
}

void ViewFormHandler::changeModelOrdering(int previous_index, int current_index) {
    emit changeOrder(mCurrentTerm, mCurrentSubject, mCurrentTheme, previous_index, current_index);
}

void ViewFormHandler::reloadGridView() {
    clearViewsFromView();
    invokeSetImages();
    mView->findChild<QObject*>("gridView")->setProperty("currentIndex", mIndex);
}

void ViewFormHandler::onOrderChanged(int previous_index, int current_index) {
    changeModelOrdering(previous_index, current_index);
    reloadGridView();
    qDebug(logDebug()) << "Model has been updated";
}

void ViewFormHandler::onUpdateImage(int index, QString name) {
    mIndex = index;
    reloadGridView();
    qDebug(logDebug()) << "Model has been updated";
}

void ViewFormHandler::onUpdateView() {
    if (ConspectModel::getConspectModel()->rowCount() == 0) {
        mCurrentTerm = -1;
        mCurrentSubject = "";
        mCurrentTheme = "";
        clearComboBoxes();
    }
    onForm();
}

void ViewFormHandler::onSetGridViewIndex(int index) {
    mIndex = index;
}

void ViewFormHandler::onSetPath() {
    emit setPathToList(mCurrentTerm, mCurrentSubject, mCurrentTheme);
}

void ViewFormHandler::onForm() {
    FormHandler::onForm();
    reloadGridView();
}
