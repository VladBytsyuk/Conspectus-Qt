#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include <QObject>

class TagHandler : public QObject
{
    Q_OBJECT
public:
    explicit TagHandler(QObject* view);
    ~TagHandler();

signals:

public slots:
    bool onSearchRequest(QString request);
};

#endif // TAGHANDLER_H
