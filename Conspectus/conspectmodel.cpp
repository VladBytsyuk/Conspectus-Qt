#include "conspectmodel.h"

ConspectModel::ConspectModel()
{
//    connect(&FileManager::)
    mConspectHierarchyModel = new QStandardItemModel();
    mListsModel = new QStandardItemModel();
}

ConspectModel* ConspectModel::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new ConspectModel();
    }
    return mInstance;
}

void ConspectModel::setConspectModel(QStandardItemModel* conspectModel) {
    mConspectHierarchyModel = conspectModel;
}

QStandardItemModel* ConspectModel::getConspectModel() {
    return mConspectHierarchyModel;
}


void ConspectModel::setListModel(QStandardItemModel* listModel) {
    mListsModel = listModel;
}

QStandardItemModel* ConspectModel::getListModel() {
    return mListsModel;
}

int ConspectModel::generateListId() {
    int max_id = -1;
    for (int row = 0; row < mListsModel->rowCount(); ++row) {
        QModelIndex rowIndex = mListsModel->index(row, 0);
        int id = rowIndex.data().toInt();
        max_id = id > max_id ? id : max_id;
    }
    return max_id + 1;
}

int ConspectModel::insertIntoListModel(QString file_name) {
    int id = generateListId();
    int row = mListsModel->rowCount();
    mListsModel->insertRow(row);

    QModelIndex idIndex = mListsModel->index(row, 0);
    mListsModel->setData(idIndex, id);

    QModelIndex fileIndex = mListsModel->index(row, 1);
    mListsModel->setData(fileIndex, file_name);

    emit insertFileDBSignal(id, file_name);
    return id;
}

bool ConspectModel::insertIntoConspectModel(int id, int term, QString subject,
                                            QString theme) {
    int row_id = generateConspectId();
    int list_no = generateListNo(term, subject, theme);
    int theme_no = getThemeNo(term, subject, theme);
    bool isInserted = insertIntoConspectModel(row_id, term, subject, theme_no, theme,
                                   list_no, id);
    if (!isInserted) return isInserted;

    emit insertListDBSignal(row_id, term, subject, theme_no, theme,
                            list_no, id);
    return true;
}

bool ConspectModel::insertIntoConspectModel(int id, int term, QString subject,
                                            int theme_no, QString theme,
                                            int list_no, int list_id) {
    int terms_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < terms_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        int current_term = termIndex.data().toInt();
        if (current_term == term) {
            int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
                QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
                QString current_subject = subjectIndex.data().toString();
                if (current_subject == subject) {
                    int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
                    for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                        QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                        QString current_theme = themeIndex.data().toString();
                        if (current_theme == theme) {
                            return insertList(&themeIndex, id, list_no, list_id);
                        }
                    }
                    return insertTheme(&subjectIndex, theme_no, theme, id, list_no, list_id);
                }
            }
            return insertSubject(&termIndex, subject, theme_no, theme, id, list_no, list_id);
        }
    }
    return insertTerm(term, subject, theme_no, theme, id, list_no, list_id);
}

bool ConspectModel::insertList(QModelIndex* index, int id, int list_no, int list_id) {
    int rows = mConspectHierarchyModel->rowCount(*index);
    mConspectHierarchyModel->insertRow(rows, *index);
    QModelIndex listIdIndex = mConspectHierarchyModel->index(rows, 0, *index);
    QModelIndex listNoIndex = mConspectHierarchyModel->index(rows, 1, *index);
    QModelIndex idIndex = mConspectHierarchyModel->index(rows, 2, *index);
    mConspectHierarchyModel->setData(listIdIndex, list_id);
    mConspectHierarchyModel->setData(listNoIndex, list_no);
    mConspectHierarchyModel->setData(idIndex, id);
    return true;
}

bool ConspectModel::insertTheme(QModelIndex* index, int theme_no, QString theme,
                                int id, int list_no, int list_id) {
    int rows = mConspectHierarchyModel->rowCount(*index);
    mConspectHierarchyModel->insertRow(rows, *index);
    QModelIndex themeIndex = mConspectHierarchyModel->index(rows, 0, *index);
    QModelIndex themeNoIndex = mConspectHierarchyModel->index(rows, 1, *index);
    mConspectHierarchyModel->setData(themeIndex, theme);
    mConspectHierarchyModel->setData(themeNoIndex, theme_no);
    insertList(&themeIndex, id, list_no, list_id);
    return true;
}

bool ConspectModel::insertSubject(QModelIndex* index, QString subject, int theme_no, QString theme,
                                  int id, int list_no, int list_id) {
    int rows = mConspectHierarchyModel->rowCount(*index);
    mConspectHierarchyModel->insertRow(rows, *index);
    QModelIndex subjectIndex = mConspectHierarchyModel->index(rows, 0, *index);
    mConspectHierarchyModel->setData(subjectIndex, subject);
    insertTheme(&subjectIndex, theme_no, theme, id, list_no, list_id);
    return true;
}

bool ConspectModel::insertTerm(int term, QString subject, int theme_no,
                               QString theme, int id, int list_no, int list_id) {
    int rows = mConspectHierarchyModel->rowCount();
    mConspectHierarchyModel->insertRow(rows);
    QModelIndex termIndex = mConspectHierarchyModel->index(rows, 0);
    mConspectHierarchyModel->setData(termIndex, term);
    insertSubject(&termIndex, subject, theme_no, theme, id, list_no, list_id);
    return true;
}

int ConspectModel::generateConspectId() {
    int max_id = -1;
    int row_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < row_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
        for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
            QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
            int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
            for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                for (int listIterator = 0; listIterator < lists_count; ++listIterator) {
                    QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 2, themeIndex);
                    int current_id = idIndex.data().toInt();
                    max_id = (max_id < current_id ? current_id : max_id);
                }
            }
        }
    }
    if (max_id == -1) {
        qCritical(logCritical()) << "Can't generate index for Conspect Model";
        return max_id;
    }
    return max_id + 1;
}

int ConspectModel::generateListNo(int term, QString subject, QString theme) {
    int max_id = -1;
    int row_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < row_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        if (termIndex.data().toInt() == term) {
            int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
                QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
                if (subjectIndex.data().toString() == subject) {
                    int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
                    for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                        QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                        if (themeIndex.data().toString() == theme) {
                            int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                            for (int listIterator = 0; listIterator < lists_count; ++listIterator) {
                                QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 1, themeIndex);
                                int current_id = idIndex.data().toInt();
                                max_id = (max_id < current_id ? current_id : max_id);
                            }
                        }
                        continue;
                    }
                }
                continue;
            }
        }
        continue;
    }

    if (max_id == -1) {
        qCritical(logCritical()) << "Can't generate list_no for Conspect Model";
        return 1;
    }
    return max_id + 1;
}

int ConspectModel::getThemeNo(int term, QString subject, QString theme) {
    int max_no = -1;
    int row_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < row_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        if (termIndex.data().toInt() == term) {
            int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
                QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
                if (subjectIndex.data().toString() == subject) {
                    int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
                    for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                        QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                        QModelIndex themeNoIndex = mConspectHierarchyModel->index(themeIterator, 1, subjectIndex);
                        int theme_no = themeNoIndex.data().toInt();
                        max_no = (max_no < theme_no ? theme_no : max_no);
                        if (themeIndex.data().toString() == theme) {
                            return themeNoIndex.data().toInt();
                        }
                    }
                }
                continue;
            }
        }
        continue;
    }

    if (max_no == -1) {
        qCritical(logCritical()) << "Can't get theme_no for Conspect Model";
        return 1;
    }
    return max_no + 1;
}


bool ConspectModel::removeFile(QString file_name) {
    int row = -1;
    int rows_count = mListsModel->rowCount();

    for (int i = 0; i < rows_count; ++i) {
        QModelIndex index = mListsModel->index(i, 1);
        if (index.data().toString() == file_name) {
            row = i;
            i = rows_count;
        }
    }
    if (row == -1) {
        qDebug() << "Can`t remove file from model, "
                 << "because model doesn't consist this file name: "
                 << file_name;
        return false;
    }
    mListsModel->removeRow(row);

    return true;
}

void ConspectModel::onRemoveFile(QString file_name) {
    this->removeFile(file_name);
    emit removeFileDBSignal(file_name);
}

void ConspectModel::onAddFile(QString file_name, int term, QString subject, QString theme) {
    int id = insertIntoListModel(file_name);
    insertIntoConspectModel(id, term, subject, theme);
}

void ConspectModel::onChangeOrdering(int term, QString subject, QString theme, int previous_index, int current_index) {
    int terms_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < terms_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        int current_term = termIndex.data().toInt();
        if (current_term == term) {
            int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
            for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
                QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
                QString current_subject = subjectIndex.data().toString();
                if (current_subject == subject) {
                    int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
                    for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                        QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                        QString current_theme = themeIndex.data().toString();
                        if (current_theme == theme) {
                            QModelIndex themeNoIndex = mConspectHierarchyModel->index(themeIterator, 1, subjectIndex);
                            int theme_no = themeNoIndex.data().toInt();
                            int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                            for (int listIterator = 0; listIterator < lists_count; ++ listIterator) {
                                QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 2, themeIndex);
                                int id = idIndex.data().toInt();
                                QModelIndex listIdIndex = mConspectHierarchyModel->index(listIterator, 0, themeIndex);
                                int list_id = listIdIndex.data().toInt();
                                QModelIndex listNoIndex = mConspectHierarchyModel->index(listIterator, 1, themeIndex);
                                int current_list_no = listNoIndex.data().toInt();
                                current_list_no--;

                                bool isDragForward = previous_index < current_index;
                                if (isDragForward) {
                                    if (current_list_no == previous_index) {
                                        current_list_no = current_index;
                                    } else if (current_list_no >= previous_index + 1 && current_list_no <= current_index) {
                                        current_list_no--;
                                    }
                                } else {
                                    if (current_list_no == current_index) {
                                        current_list_no = previous_index;
                                    } else if (current_list_no >= current_index && current_list_no <= previous_index - 1) {
                                        current_list_no++;
                                    }
                                }

                                current_list_no++;
                                mConspectHierarchyModel->setData(listNoIndex, current_list_no);
                                emit updateRowInConspectTable(id, term, subject, theme_no, theme, current_list_no, list_id);
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
}

/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel =
        new QStandardItemModel(0, 3);
QStandardItemModel* ConspectModel::mListsModel =
        new QStandardItemModel(0, 1);
