#ifndef _GLEW_H_INCLUDE
#define _GLEW_H_INCLUDE

#ifdef WIN32
    // Variable GLEW_DIR must be set.
    #include "glew.h"
#else
    // When installed, glew is located at usr/include/GL, which is alreay in the PATH environment variable.
    #include "GL/glew.h"
#endif

#include <string>
#include <QtOpenGLWidgets/QOpenGLWidget>

// Shader API
GLuint read_program(const char *filename, const char *definitions = "");
int release_program(const GLuint program);
int reload_program(const GLuint program, const char *filename, const char *definitions = "");
int program_format_errors(const GLuint program, std::string& errors);
int program_print_errors(const GLuint program);

#endif
