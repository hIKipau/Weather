QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network
QT += multimedia multimediawidgets
QT += sql
CONFIG += c++17
CONFIG += sdk_no_version_check

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/videos/фон.mp4

# MacOS specific configuration
macx {
    LIBS += -L/opt/homebrew/Cellar/libpq/17.0_1/lib -lpq
    INCLUDEPATH += /opt/homebrew/Cellar/libpq/17.0_1/include

    # Добавляем дополнительные пути поиска библиотек
    QMAKE_RPATHDIR += /opt/homebrew/lib/postgresql@14
    QMAKE_RPATHDIR += /opt/homebrew/Cellar/postgresql@14/14.13_2/lib/postgresql@14
}
