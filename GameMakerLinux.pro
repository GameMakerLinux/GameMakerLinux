QT       += core gui widgets

TARGET = GameMakerLinux
TEMPLATE = app

CONFIG += c++17
LIBS += -lqutepart

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    models/resourcesmodel.cpp \
    docks/resourcestreedock.cpp \
    gamesettings.cpp \
    resources/dependencies/folderlayer.cpp \
    resources/dependencies/tilelayer.cpp \
    resources/html5optionsresourceitem.cpp \
    resources/spriteresourceitem.cpp \
    resources/resourceitem.cpp \
    resources/tilesetresourceitem.cpp \
    resources/tvosoptionsresourceitem.cpp \
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
    resources/windowsuapoptionsresourceitem.cpp \
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
    resources/dependencies/objectinstance.cpp \
    models/objectsmodel.cpp \
    resources/dependencies/roomsettings.cpp \
    models/sortedeventsmodel.cpp \
    resources/projectresource.cpp \
    utils/flowlayout.cpp \
    widgets/formedit.cpp

HEADERS += \
        mainwindow.h \
    models/resourcesmodel.h \
    docks/resourcestreedock.h \
    gamesettings.h \
    resources/dependencies/folderlayer.h \
    resources/dependencies/tilelayer.h \
    resources/html5optionsresourceitem.h \
    resources/spriteresourceitem.h \
    resources/resourceitem.h \
    resources/tilesetresourceitem.h \
    resources/tvosoptionsresourceitem.h \
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
    resources/windowsuapoptionsresourceitem.h \
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
    resources/dependencies/objectinstance.h \
    models/objectsmodel.h \
    resources/dependencies/roomsettings.h \
    models/sortedeventsmodel.h \
    resources/projectresource.h \
    utils/flowlayout.h \
    widgets/formedit.h

FORMS += \
        mainwindow.ui \
    editors/objecteditor.ui \
    editors/maineditor.ui \
    editors/roomeditor.ui
