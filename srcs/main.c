#include "../includes/scop.h"

const char* vertex_shader_src =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\n";

const char* fragment_shader_src =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(0.8, 0.3, 0.2, 1.0);\n"
"}\n";

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

GLuint create_shader_program( void ) {

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

int main( void ) {

	if (!glfwInit()) {

		fprintf(stderr, "Failed to initialize GLFW\n");
		return (-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // which major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // which minor versions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // which profile -> package of functions

	// Creating window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "SCOP", NULL, NULL);
	if (!window) {

		fprintf(stderr, "Failed to create window\n");
		glfwTerminate();
		return (-1);
	}

	glfwMakeContextCurrent(window); // making window part of current context 

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {

		fprintf(stderr, "Failed to initialize GLEW\n");
		return (-1);
	}

	GLfloat vertices[] = { 						// placeholder data
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	GLuint shader_program = create_shader_program();
	
	GLuint vertex_array_object, vertex_buffer_object;

	glGenVertexArrays(1, &vertex_array_object); // generate one vertex array object
	glGenBuffers(1, &vertex_buffer_object);		// generate one vertex buffer object

	glBindVertexArray(vertex_array_object);		// will bind all openGL calls related to vertex attributes to that array

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// upload loaded data to GPU
															//GL_STATIC_DRAW = opti to load once and use many times
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	while (!glfwWindowShouldClose(window)) { // making sure that the window should stay open unless closed
		
		// color of the background
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glUseProgram(shader_program); // activating shader program
		glBindVertexArray(vertex_array_object); // binding vao to tell openGL to use this specific one

		// drawing
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); //swap to update each frame

		// handle at every loop cycle all events (closing window, resizing, etc..)
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);
	glDeleteProgram(shader_program);

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
