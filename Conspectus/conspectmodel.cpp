#include "conspectmodel.h"
#include <QTreeView>

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

void ConspectModel::logConspectModel()
{
    qDebug() << "ConspectModel:";
    int terms_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < terms_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        int current_term = termIndex.data().toInt();
        qDebug() << QString::number(current_term);
        int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
        for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
            QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
            QString current_subject = subjectIndex.data().toString();
            qDebug() << "   " << current_subject;
            int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
            for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                QString current_theme = themeIndex.data().toString();
                QModelIndex themeNoIndex = mConspectHierarchyModel->index(themeIterator, 1, subjectIndex);
                QString current_theme_no = themeNoIndex.data().toString();
                qDebug() << "       " << current_theme << " (" << current_theme_no << ")";
                int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                for (int listIterator = 0; listIterator < lists_count; ++listIterator) {
                    QModelIndex listIndex = mConspectHierarchyModel->index(listIterator, 0, themeIndex);
                    QString current_list = listIndex.data().toString();
                    QModelIndex listNoIndex = mConspectHierarchyModel->index(listIterator, 1, themeIndex);
                    QString current_list_no = listNoIndex.data().toString();
                    QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 2, themeIndex);
                    QString id = idIndex.data().toString();
                    qDebug() << "           " << current_list << " (" << current_list_no << ") : id = " << id;
                }
            }
        }
    }
}

void ConspectModel::logListModel()
{

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

    qDebug() << "Inserted row into ConspectModel: (" << row_id << ", " << term << ", " << subject << ", "
             << theme_no << ", " << theme << ", " << list_no << ", " << id << ")";
    logConspectModel();
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
    qDebug() << "Insert list " << list_id << ": " << rows << " lists.";
    mConspectHierarchyModel->insertRow(rows, *index);
    if (rows == 0) mConspectHierarchyModel->insertColumns(0, 3, *index);
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
    qDebug() << "Insert theme " << theme << ": " << rows << " themes.";
    mConspectHierarchyModel->insertRow(rows, *index);
    if (rows == 0) mConspectHierarchyModel->insertColumns(0, 2, *index);
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
    qDebug() << "Insert subject " << subject << ": " << rows << " subjects.";
    mConspectHierarchyModel->insertRow(rows, *index);
    if (rows == 0) mConspectHierarchyModel->insertColumn(0, *index);
    QModelIndex subjectIndex = mConspectHierarchyModel->index(rows, 0, *index);
    mConspectHierarchyModel->setData(subjectIndex, subject);
    insertTheme(&subjectIndex, theme_no, theme, id, list_no, list_id);
    return true;
}

bool ConspectModel::insertTerm(int term, QString subject, int theme_no,
                               QString theme, int id, int list_no, int list_id) {
    int rows = mConspectHierarchyModel->rowCount();
    qDebug() << "Insert term " << term << ": " << rows << " terms in conspect.";
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
        qCritical(logCritical()) << "Empty Conspect Model";
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





int ConspectModel::getListId(QString name) {
    int list_count = mListsModel->rowCount();
    for (int i = 0; i < list_count; ++i) {
        QModelIndex file_name_index = mListsModel->index(i, 1);
        if (file_name_index.data().toString() == name) {
            QModelIndex list_id_index = mListsModel->index(i, 0);
            int list_id = list_id_index.data().toInt();
            return list_id;
        }
    }
    return 0;
}

void ConspectModel::deleteList(int term, QString subject, QString theme, QString file_name) {
    int list_id = getListId(file_name);
    deleteList(term, subject, theme, list_id);
}

void ConspectModel::deleteList(int term, QString subject, QString theme, int list_id) {
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
                            int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                            for (int listIterator = 0; listIterator < lists_count; ++listIterator) {
                                QModelIndex listIndex = mConspectHierarchyModel->index(listIterator, 0, themeIndex);
                                int current_list = listIndex.data().toInt();
                                QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 2, themeIndex);
                                int row_id = idIndex.data().toInt();
                                if (current_list == list_id) {
                                    mConspectHierarchyModel->removeRow(listIterator, themeIndex);
                                    emit removeRowFromConspectDB(row_id);
                                    if (mConspectHierarchyModel->rowCount(themeIndex) == 0) {
                                        mConspectHierarchyModel->removeRow(themeIterator, subjectIndex);
                                        if (mConspectHierarchyModel->rowCount(subjectIndex) == 0) {
                                            mConspectHierarchyModel->removeRow(subjectIterator, termIndex);
                                            if (mConspectHierarchyModel->rowCount(termIndex) == 0) {
                                                mConspectHierarchyModel->removeRow(termIterator);
                                            }
                                        }
                                    }
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool ConspectModel::isImageUsed(QString name) {
    int list_id = getListId(name);
    return isImageUsed(list_id);
}

bool ConspectModel::isImageUsed(int list_id) {
    int terms_count = mConspectHierarchyModel->rowCount();
    for (int termIterator = 0; termIterator < terms_count; ++termIterator) {
        QModelIndex termIndex = mConspectHierarchyModel->index(termIterator, 0);
        int subjects_count = mConspectHierarchyModel->rowCount(termIndex);
        for (int subjectIterator = 0; subjectIterator < subjects_count; ++subjectIterator) {
            QModelIndex subjectIndex = mConspectHierarchyModel->index(subjectIterator, 0, termIndex);
            int themes_count = mConspectHierarchyModel->rowCount(subjectIndex);
            for (int themeIterator = 0; themeIterator < themes_count; ++themeIterator) {
                QModelIndex themeIndex = mConspectHierarchyModel->index(themeIterator, 0, subjectIndex);
                int lists_count = mConspectHierarchyModel->rowCount(themeIndex);
                for (int listIterator = 0; listIterator < lists_count; ++listIterator) {
                    QModelIndex idIndex = mConspectHierarchyModel->index(listIterator, 0, themeIndex);
                    int id = idIndex.data().toInt();
                    if (id == list_id) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void ConspectModel::changeTag(int list_id, QString file_name, QString tag) {
    int row_count = mListsModel->rowCount();
    QString comment = "";
    for (int i = 0; i < row_count; ++i) {
        QModelIndex idIndex = mListsModel->index(i, 0);
        if (idIndex.data().toInt() == list_id) {
            QModelIndex tagIndex = mListsModel->index(i, 2);
            mListsModel->setData(tagIndex, tag);
            QModelIndex commentIndex = mListsModel->index(i, 3);
            comment = commentIndex.data().toString();
        }
    }
    emit insertListTableDBSignal(list_id, file_name, tag, comment);
}

void ConspectModel::changeComment(int list_id, QString file_name, QString comment) {
    int row_count = mListsModel->rowCount();
    QString tag = "";
    for (int i = 0; i < row_count; ++i) {
        QModelIndex idIndex = mListsModel->index(i, 0);
        if (idIndex.data().toInt() == list_id) {
            QModelIndex commentIndex = mListsModel->index(i, 3);
            mListsModel->setData(commentIndex, comment);
            QModelIndex tagIndex = mListsModel->index(i, 2);
            tag = tagIndex.data().toString();
        }
    }
    emit insertListTableDBSignal(list_id, file_name, tag, comment);
}

QStringList ConspectModel::getFileNamesByTag(QString tag) {
    QStringList fileNames;
    if (tag.simplified() == "") return fileNames;
    QStringList tags = tag.simplified().split(" ");
    int row = mListsModel->rowCount();
    for (int i = 0; i < row; ++i) {
        QModelIndex tagIndex = mListsModel->index(i, 2);
        QStringList currentTags = tagIndex.data().toString().split(" ");
        bool isAllTags = true;
        for (int j = 0; j < tags.size(); ++j) {
            if (!currentTags.contains(tags.at(j))) isAllTags = false;
        }
        if (isAllTags) {
            QModelIndex nameIndex = mListsModel->index(i, 1);
            fileNames.append(nameIndex.data().toString());
        }
    }
    return fileNames;
}

void ConspectModel::onRemoveList(int term, QString subject, QString theme, QString file_name) {
    deleteList(term, subject, theme, file_name);
    logConspectModel();
    if (!isImageUsed(file_name)) {
        emit tryToRemoveFile(file_name);
    }
}

void ConspectModel::onRemoveFile(QString file_name) {   
    this->removeFile(file_name);
    logConspectModel();
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
                                int prev_list_no = current_list_no;
                                current_list_no--;

                                bool isDragForward = previous_index < current_index;
                                if (isDragForward) {
                                    if (current_list_no == previous_index) {
                                        current_list_no = current_index;
                                    } else if (current_list_no >= previous_index + 1 && current_list_no <= current_index) {
                                        current_list_no--;
                                    }
                                } else {
                                    if (current_list_no == previous_index) {
                                        current_list_no = current_index;
                                    } else if (current_list_no >= current_index && current_list_no <= previous_index - 1) {
                                        current_list_no++;
                                    }
                                }

                                current_list_no++;
                                if (current_list_no != prev_list_no) {
                                    mConspectHierarchyModel->setData(listNoIndex, current_list_no);
                                    emit updateRowInConspectTable(id, term, subject, theme_no, theme, current_list_no, list_id);
                                }
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
    logConspectModel();
}

void ConspectModel::onAddListToAnotherPath(int term, QString subject, QString theme, QString file_name) {
    int list_id = getListId(file_name);
    insertIntoConspectModel(list_id, term, subject, theme);
}

void ConspectModel::onChangeTag(QString file_name, QString tag) {
    int list_id = getListId(file_name);
    changeTag(list_id, file_name, tag);
}

void ConspectModel::onChangeComment(QString file_name, QString comment) {
    int list_id = getListId(file_name);
    changeComment(list_id, file_name, comment);
}

/* ================= Fields initialization ================= */
ConspectModel* ConspectModel::mInstance = nullptr;
QStandardItemModel* ConspectModel::mConspectHierarchyModel =
        new QStandardItemModel(0, 3);
QStandardItemModel* ConspectModel::mListsModel =
        new QStandardItemModel(0, 1);
