TEMPLATE = lib
SUBDIRS = lib

MVE_ROOT = ../../../../../mve/

CONFIG += qt opengl plugin
QT += opengl

QMAKE_CXXFLAGS += -fPIC -fopenmp -O3 -std=c++0x
QMAKE_LFLAGS += -rdynamic

SOURCES += [^_]*.cc $${MVE_ROOT}/apps/umve/mainwindowtab.cc $${MVE_ROOT}/apps/umve/glwidget.cc
HEADERS += *.h $${MVE_ROOT}/apps/umve/mainwindowtab.h $${MVE_ROOT}/apps/umve/glwidget.h $${MVE_ROOT}/apps/umve/scene_addins/addin_base.h
TARGET = ~/.local/share/umve/plugins/$$qtLibraryTarget(RegioningTab)

INCLUDEPATH += $${MVE_ROOT}/libs $${MVE_ROOT}/apps/umve  $${MVE_ROOT}/apps/umve/viewinspect $${MVE_ROOT}/../mve-extern ../../libs/regioning include
DEPENDPATH += $${MVE_ROOT}/libs ../../libs/regioning
LIBS = $${MVE_ROOT}/libs/dmrecon/libmve_dmrecon.a $${MVE_ROOT}/libs/mve/libmve.a $${MVE_ROOT}/libs/ogl/libmve_ogl.a $${MVE_ROOT}/libs/util/libmve_util.a libs/libcsc.a -lpng -ljpeg -ltiff -lGLEW -fopenmp -ffast-math
QMAKE_LIBDIR_QT =

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

RESOURCES += \
    regioning_plugin.qrc
