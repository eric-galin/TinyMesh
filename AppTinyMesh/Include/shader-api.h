#ifndef _GLEW_H_INCLUDE
#define _GLEW_H_INCLUDE

#ifdef _WIN32
    // Environment variable GLEW_DIR must be set.
    #include "glew.h"
#elif __APPLE__
	// glew path for macOs
    #include "GL/glew.h"
#else
    // When installed on unix (and macOs ?), glew is located at usr/include/GL, which is alreay in the PATH environment variable.
    #include "GL/glew.h"
#endif

// QGlobal is needed to check the Qt version
#include <QtCore/qglobal.h>

// QOpenGLWidget location depends on Qt version (differs between Qt6 & Qt5)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QtWidgets/QOpenGLWidget>
#else
    #include <QtOpenGLWidgets/QOpenGLWidget>
#endif

#include <string>

// Shader API
GLuint read_program(const char *filename, const char *definitions = "");
int release_program(const GLuint program);
int reload_program(const GLuint program, const char *filename, const char *definitions = "");
int program_format_errors(const GLuint program, std::string& errors);
int program_print_errors(const GLuint program);

#endif
