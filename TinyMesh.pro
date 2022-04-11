#-------------------------------------------------
#
# Project created by QtCreator 2021-10-19T21:55:17
#
#-------------------------------------------------

QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyMesh
TEMPLATE = app

SOURCES += AppTinyMesh/Source/box.cpp \
    AppTinyMesh/Source/camera.cpp \
    AppTinyMesh/Source/evector.cpp \
    AppTinyMesh/Source/main.cpp \
    AppTinyMesh/Source/mesh-widget.cpp \
    AppTinyMesh/Source/mesh.cpp \
    AppTinyMesh/Source/meshcolor.cpp \
    AppTinyMesh/Source/qtemainwindow.cpp \
    AppTinyMesh/Source/ray.cpp \
    AppTinyMesh/Source/shader-api.cpp \
    AppTinyMesh/Source/triangle.cpp

HEADERS  += AppTinyMesh/Include/qte.h \
    AppTinyMesh/Include/GL.h \
    AppTinyMesh/Include/box.h \
    AppTinyMesh/Include/camera.h \
    AppTinyMesh/Include/color.h \
    AppTinyMesh/Include/glew.h \
    AppTinyMesh/Include/mathematics.h \
    AppTinyMesh/Include/mesh.h \
    AppTinyMesh/Include/meshcolor.h \
    AppTinyMesh/Include/qte.h \
    AppTinyMesh/Include/ray.h \
    AppTinyMesh/Include/realtime.h \
    AppTinyMesh/Include/shader-api.h \
    AppTinyMesh/Include/ui-interface.h

FORMS    += \
    AppTinyMesh/UI/interface.ui

INCLUDEPATH += AppTinyMesh/Include/

release: DESTDIR = Out/Release
debug:   DESTDIR = Out/Debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

#---- Comment the following line on MacOS/Linux
LIBS = -lGLU -lGLEW

#---- Uncomment the following line on Windows
#LIBS += -lglu32
#LIBS += -lglew32
#LIBS += -lOpengl32

DISTFILES += \
    Shaders/mesh.glsl \
    Shaders/skybox.glsl

