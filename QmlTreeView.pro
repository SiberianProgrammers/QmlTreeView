QT += quick

TEMPLATE += subdirs

INCLUDEPATH += $$PWD/src/include

HEADERS += \
    $$PWD/src/include/QmlTool.h \
    $$PWD/src/include/TreeItem.h \
    $$PWD/src/include/TreeItemModel.h \
    $$PWD/src/include/QmlTreeViewRegister.h \
    $$PWD/src/include/RootItem.h \
    $$PWD/src/include/TreeItemInterface.h

SOURCES += \
    $$PWD/src/source/TreeItemInterface.cpp \
    $$PWD/src/source/TreeItemModel.cpp \
    $$PWD/src/source/RootItem.cpp

RESOURCES += \
    $$PWD/src/qml/TreeViewQml.qrc \
    $$PWD/images/images.qrc

