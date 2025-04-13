#ifndef SCOP_H
# define SCOP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLuint create_shader( GLenum type, const char* src );
GLuint create_shader_program( void );

#endif