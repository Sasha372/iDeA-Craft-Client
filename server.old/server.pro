QT += gui core widgets
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG -= debug_and_release debug_and_release_target

# Разделяем по директориям все выходные файлы проекта
MOC_DIR = $$OUT_PWD/common/Client/build
RCC_DIR = $$OUT_PWD/common/Client/build
UI_DIR = $$OUT_PWD/common/Client/build
unix:OBJECTS_DIR = $$OUT_PWD/common/Client/build/o/unix
win32:OBJECTS_DIR = $$OUT_PWD/common/Client/build/o/win32
macx:OBJECTS_DIR = $$OUT_PWD/common/Client/build/o/mac

TARGET = ../idea-server

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
		main.cpp \
		server.cpp \
		connection.cpp \
		connectdb.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
		server.h \
		connection.h \
		connectdb.h