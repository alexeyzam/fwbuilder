include(../../../../qmake.inc)

QT += testlib network gui
CONFIG += console
CONFIG -= app_bundle
TARGET = startTipDialogTest

HEADERS += startTipDialogTest.h

SOURCES += main_startTipDialogTest.cpp \
    startTipDialogTest.cpp

RESOURCES += ../../MainRes.qrc
LIBS += ../../libgui.a
CONFIG -= release
CONFIG += debug
LIBS += $$LIBS_FWCOMPILER $$LIBS_FWBUILDER $$CPPUNIT_LIBS
OBJECTS_DIR = ../../.obj
MOC_DIR = ../../.moc

INCLUDEPATH += ../../.ui
INCLUDEPATH += ../../../compiler_lib
INCLUDEPATH += ../../../iptlib
INCLUDEPATH += ../../../.. \
../../../cisco_lib \
../../../pflib \
../../.. ../..

DEPENDPATH = ../../../common

!win32:LIBS += ../../../common/libcommon.a
!win32:PRE_TARGETDEPS = ../../../common/libcommon.a

win32:CONFIG += console

win32:LIBS += ../../../common/release/common.lib
win32:PRE_TARGETDEPS = ../../../common/release/common.lib

run_tests.commands = echo "Running tests..."; \
    ./${TARGET}
run_tests.depends = build_tests
build_tests.depends = all
clean_tests.depends = all
QMAKE_EXTRA_TARGETS += run_tests build_tests clean_tests


INCLUDEPATH += $$ANTLR_INCLUDEPATH
LIBS += ../../$$FWBPARSER_LIB $$ANTLR_LIBS
DEFINES += $$ANTLR_DEFINES

LIBS += $$LIBS_FWCOMPILER

# fwtransfer lib. Add this before adding -lQtDBus to LIBS below
LIBS += ../../$$FWTRANSFER_LIB
contains( HAVE_QTDBUS, 1 ):unix {
    !macx:QT += network \
        dbus
    macx:LIBS += -framework \
        QtDBus
}

HEADERS += ../../transferDialog.h
SOURCES += ../../transferDialog.cpp

# !macx:LIBS += -lQtDBus # workaround for QT += dbus not working with Qt < 4.4.0
INCLUDEPATH += ../../../common \
        ../../../iptlib \
    ../../../pflib \
    ../../../cisco_lib/ \
    ../../../compiler_lib/
DEPENDPATH = ../../../common \
        ../../../iptlib \
    ../../../pflib \
    ../../../cisco_lib/ \
    ../../../compiler_lib
win32:LIBS += ../../../common/release/common.lib \
        ../../../iptlib/release/iptlib.lib \
    ../../../pflib/release/fwbpf.lib \
    ../../../cisco_lib/release/fwbcisco.lib \
    ../../../compiler_lib/release/compilerdriver.lib
!win32:LIBS += ../../../common/libcommon.a \
        ../../../iptlib/libiptlib.a \
    ../../../pflib/libfwbpf.a \
    ../../../cisco_lib/libfwbcisco.a \
    ../../../compiler_lib/libcompilerdriver.a
win32:PRE_TARGETDEPS = ../../../common/release/common.lib \
        ../../../iptlib/release/iptlib.lib \
    ../../../pflib/release/fwbpf.lib \
    ../../../cisco_lib/release/fwbcisco.lib \
    ../../../compiler_lib/release/compilerdriver.lib
!win32:PRE_TARGETDEPS = ../../../common/libcommon.a \
        ../../../iptlib/libiptlib.a \
    ../../../pflib/libfwbpf.a \
    ../../../cisco_lib/libfwbcisco.a \
    ../../../compiler_lib/libcompilerdriver.a
