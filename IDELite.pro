#-------------------------------------------------
#
# Project created by QtCreator 2022-08-26T17:46:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IDELite
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        IDELite.cpp \
    MenuButton.cpp \
    MainMenu.cpp \
    ScreenButton.cpp \
    FileNameLabel.cpp \
    PlainTextEdit.cpp \
    FileList.cpp \
    HighLighter.cpp \
    StartWidget.cpp \
    Comleter.cpp \
    functionlist.cpp \
    replacemainwindow.cpp \
    searchstring.cpp \
    consolewidget.cpp \
    debugmainwindow.cpp \

HEADERS += \
        IDELite.h \
    MoveWgt.h \
    DragWgt.h \
    MenuButton.h \
    MainMenu.h \
    ScreenButton.h \
    FileNameLabel.h \
    PlainTextEdit.h \
    FileList.h \
    HighLighter.h \
    StartWidget.h \
    Comleter.h \
    functionlist.h \
    replacemainwindow.h \
    searchstring.h \
    consolewidget.h \
    debugmainwindow.h \

#RESOURCES += \
#    resources.qrc

FORMS += \
    replacemainwindow.ui \
    debugmainwindow.ui

RC_ICONS = code.ico
