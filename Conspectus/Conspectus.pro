TEMPLATE = app

QT += qml quick widgets
QT += sql
QT += printsupport
QT += widgets

CONFIG += c++11

SOURCES += \
    conspectmodel.cpp \
    main.cpp \
    dbmanager.cpp \
    filemanager.cpp \
    loggingcategories.cpp \
    addformhandler.cpp \
    formhandler.cpp \
    viewformhandler.cpp \
    utils.cpp \
    resourceimageprovider.cpp \
    imagehandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dbmanager.h \
    conspectmodel.h \
    filemanager.h \
    loggingcategories.h \
    addformhandler.h \
    formhandler.h \
    viewformhandler.h \
    utils.h \
    resourceimageprovider.h \
    imagehandler.h
