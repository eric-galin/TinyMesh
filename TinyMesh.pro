#-------------------------------------------------
#
# Project created by QtCreator 2021-10-19T21:55:17
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyMesh
TEMPLATE = app

SOURCES += Source/box.cpp \
    Source/camera.cpp \
    Source/evector.cpp \
    Source/main.cpp \
    Source/mesh-widget.cpp \
    Source/mesh.cpp \
    Source/meshcolor.cpp \
    Source/qtemainwindow.cpp \
    Source/ray.cpp \
    Source/shader-api.cpp \
    Source/triangle.cpp

HEADERS  += mainwindow.h \
    Include/GL.h \
    Include/box.h \
    Include/camera.h \
    Include/color.h \
    Include/evector.h \
    Include/glew.h \
    Include/mathematics.h \
    Include/mesh.h \
    Include/meshcolor.h \
    Include/qte.h \
    Include/ray.h \
    Include/realtime.h \
    Include/shader-api.h \
    Include/ui-interface.h

FORMS    += \
    UI/interface.ui

INCLUDEPATH += Include/

#---- Comment the following line on MacOS
LIBS = -lGLU -lGLEW

#---- Uncomment the following line on Windows
#LIBS += -lglu32
#LIBS += -lglew32
#LIBS += -lOpengl32

DISTFILES += \
    Shaders/mesh.glsl \
    Shaders/skybox.glsl

