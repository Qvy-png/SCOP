#ifndef SCOP_H
# define SCOP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "shaders.h"

GLuint create_shader( GLenum type, const char* src );
GLuint create_shader_program( char *vertex_shader_src, char *fragment_shader_src );

#endif