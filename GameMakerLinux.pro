#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T18:34:15
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameMakerLinux
TEMPLATE = app

CONFIG += qscintilla2 c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    models/resourcesmodel.cpp \
    docks/resourcestreedock.cpp \
    gamesettings.cpp \
    resources/spriteresourceitem.cpp \
    resources/resourceitem.cpp \
    resources/unknownresourceitem.cpp \
    resources/folderresourceitem.cpp \
    resources/objectresourceitem.cpp \
    resources/roomresourceitem.cpp \
    resources/scriptresourceitem.cpp \
    resources/mainoptionsresourceitem.cpp \
    resources/iosoptionsresourceitem.cpp \
    resources/includedfileresourceitem.cpp \
    resources/amazonfireoptionsresourceitem.cpp \
    resources/linuxoptionsresourceitem.cpp \
    resources/windowsoptionsresourceitem.cpp \
    resources/androidoptionsresourceitem.cpp \
    resources/macoptionsresourceitem.cpp \
    editors/objecteditor.cpp \
    editors/maineditor.cpp \
    widgets/codeeditor.cpp \
    editors/scripteditor.cpp \
    utils/gmlhighlighter.cpp \
    editors/roomeditor.cpp \
    models/layersmodel.cpp \
    graphics/graphicslayer.cpp \
    utils/utils.cpp \
    utils/uuid.cpp \
    models/eventsmodel.cpp \
    resources/soundresourceitem.cpp \
    resources/fontresourceitem.cpp \
    resources/dependencies/objectevent.cpp \
    widgets/selectitem.cpp \
    resources/dependencies/spriteframe.cpp \
    resources/dependencies/spriteimage.cpp \
    resources/dependencies/instancelayer.cpp \
    resources/dependencies/roomlayer.cpp \
    resources/dependencies/backgroundlayer.cpp \
    models/itemmodel.cpp \
    graphics/graphicsinstance.cpp \
    resources/dependencies/objectinstance.cpp

HEADERS += \
        mainwindow.h \
    models/resourcesmodel.h \
    docks/resourcestreedock.h \
    gamesettings.h \
    resources/spriteresourceitem.h \
    resources/resourceitem.h \
    resources/unknownresourceitem.h \
    resources/folderresourceitem.h \
    resources/objectresourceitem.h \
    resources/roomresourceitem.h \
    resources/scriptresourceitem.h \
    resources/mainoptionsresourceitem.h \
    resources/iosoptionsresourceitem.h \
    resources/includedfileresourceitem.h \
    resources/amazonfireoptionsresourceitem.h \
    resources/linuxoptionsresourceitem.h \
    resources/windowsoptionsresourceitem.h \
    resources/androidoptionsresourceitem.h \
    resources/macoptionsresourceitem.h \
    resources/allresourceitems.h \
    editors/objecteditor.h \
    editors/alleditors.h \
    editors/maineditor.h \
    widgets/codeeditor.h \
    editors/scripteditor.h \
    utils/gmlhighlighter.h \
    editors/roomeditor.h \
    models/layersmodel.h \
    graphics/graphicslayer.h \
    utils/utils.h \
    utils/uuid.h \
    models/eventsmodel.h \
    resources/soundresourceitem.h \
    resources/fontresourceitem.h \
    resources/dependencies/objectevent.h \
    widgets/selectitem.h \
    resources/dependencies/spriteframe.h \
    resources/dependencies/spriteimage.h \
    resources/dependencies/instancelayer.h \
    resources/dependencies/roomlayer.h \
    resources/dependencies/backgroundlayer.h \
    models/itemmodel.h \
    graphics/graphicsinstance.h \
    resources/dependencies/objectinstance.h

FORMS += \
        mainwindow.ui \
    editors/objecteditor.ui \
    editors/maineditor.ui \
    editors/roomeditor.ui
