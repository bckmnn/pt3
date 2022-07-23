CONFIG += c++17

TEMPLATE = app
VERSION = 0.9.0

DEFINES += APP_VERSION="$$VERSION"
DEFINES += GIT_VERSION=$$system(git describe --always)


APP_NAME = PT3
DEFINES += APP_NAME="$$APP_NAME"

APP_UNIX_NAME = pt3
DEFINES += APP_UNIX_NAME="$$APP_UNIX_NAME"

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

DESTDIR = build/target/
OBJECTS_DIR = build/obj/
MOC_DIR = build/moc/
RCC_DIR = build/rcc/


SOURCES += \
    mainwindow.cpp \
    src/constants.cpp \
    src/main.cpp

HEADERS += \
    mainwindow.h \
    src/constants.h

FORMS += \
    mainwindow.ui
