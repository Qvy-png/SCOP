#include "../includes/shaders.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char* read_file(const char* filename)	{

	size_t	capacity = 1024;
    size_t	length = 0;
	char	line[512];
    size_t	line_len;
	char	*buffer;
	FILE	*file;
	char	*temp;

	file = fopen(filename, "r");
    if (!file)
    	return (NULL);

    buffer = malloc(capacity);
    if (!buffer)
        return (fclose(file), NULL);

    while (fgets(line, sizeof(line), file)) {

        line_len = strlen(line);
        if (length + line_len + 1 > capacity) {
		
            capacity *= 2;
            temp = realloc(buffer, capacity);
            if (!temp)
                return (free(buffer), fclose(file), NULL);
            buffer = temp;
        }
        strcpy(buffer + length, line);
        length += line_len;
    }
    return (fclose(file), buffer);
}

GLuint create_shader( GLenum type, const char* src ) {

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		fprintf(stderr, "Shader compile error: %s\n", infoLog);
	}

	return shader;
}

GLuint create_shader_program( char *vertex_shader_src, char *fragment_shader_src ) {

	GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_src);
	GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_src);

	GLuint program = glCreateProgram();

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program); //wrap up

	int success; //checking on the shaders
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		fprintf(stderr, "Program linking error: %s\n", infoLog);
	}

	// deleting because the shaders are already loaded into the program
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (program);
}