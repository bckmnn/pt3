CONFIG += c++17

TEMPLATE = app
VERSION = 0.9.0

DEFINES += APPVERSION="$$VERSION"
DEFINES += GITVERSION=$$system(git describe --always)

QMAKE_TARGET_BUNDLE_PREFIX = com.bckmnn
QMAKE_BUNDLE = pt3

APP_NAME = PT3
DEFINES += APP_NAME="$$APP_NAME"

APP_UNIX_NAME = pt3
DEFINES += APP_UNIX_NAME="$$APP_UNIX_NAME"

DEFINES += ORGNAME="bckmnn"
DEFINES += ORGDOMAIN="pt3.bckmnn.com"

message(Building $${APP_NAME} $${VERSION})
message(Qt $$[QT_VERSION] in $$[QT_INSTALL_PREFIX])

CONFIG -= debug_and_release
CONFIG(debug, debug|release): {
    message(Building for debug)
}
CONFIG(release, debug|release): {
    message(Building for release)
    DEFINES *= QT_NO_DEBUG_OUTPUT
    CONFIG += optimize_full
}

DEFINES *= QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_DEPRECATED_WARNINGS

TARGET = $${APP_UNIX_NAME}

include(lib/http/http.pri)

DEFINES += UPDATER_NO_SPARKLE
include(lib/updater/updater.pri)

QT += core gui quick widgets quickwidgets network

DESTDIR = ./
OBJECTS_DIR = build/obj/
MOC_DIR = build/moc/
RCC_DIR = build/rcc/


SOURCES += \
    src/mainwindow.cpp \
    src/constants.cpp \
    src/logger.cpp \
    src/main.cpp \
    src/qmlwidget.cpp

HEADERS += \
    src/mainwindow.h \
    src/constants.h \
    src/logger.h \
    src/qmlwidget.h

FORMS += \
    src/mainwindow.ui

DISTFILES += \
    .astylerc

RESOURCES += \
    src/fonts.qrc
