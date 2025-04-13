#ifndef SHADERS_H
# define SHADERS_H

# include "scop.h"

char* read_file(const char* filename);
GLuint create_shader( GLenum type, const char* src );
GLuint create_shader_program( char *vertex_shader_src, char *fragment_shader_src );

#endif