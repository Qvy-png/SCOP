#include "../includes/scop.h"
#define VERTEX_SHADER_PATH "srcs/shaders/default.vert"
#define FRAGMENT_SHADER_PATH "srcs/shaders/default.frag"

int main( void ) {

	char	*vertex_shader_src;
	char	*fragment_shader_src = NULL;

	vertex_shader_src = read_file(VERTEX_SHADER_PATH);
	fragment_shader_src = read_file(FRAGMENT_SHADER_PATH);

	if (!glfwInit()) {

		fprintf(stderr, "Failed to initialize GLFW\n");
		return (-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // which major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // which minor versions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // which profile -> package of functions

	// Creating window object
	GLFWwindow* window = glfwCreateWindow(800, 800, "SCOP", NULL, NULL);
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

	GLfloat vertices[] = {
		-0.5f, -0.5f * sqrt(3) / 3, 0.0f,		// lower left corner
		0.5f, -0.5f * sqrt(3) / 3, 0.0f,		// lower right
		0.0f,  0.5f * sqrt(3) * 2 / 3, 0.0f,		// upper corner
		-0.5 / 2, 0.5f * sqrt(3) / 6, 0.0f,	// inner top left corner
		0.5f / 2, 0.5f * sqrt(3) / 6, 0.0f,		// inner top right corner
		0.0f, -0.5f * sqrt(3) / 3, 0.0f			// inner down
	};

	GLuint indices[] =
	{
		0, 3, 5,	// lower left triangle
		3, 2, 4,	// lower right triangle
		5, 4, 1		// upper triangle
	};

	GLuint shader_program = create_shader_program(vertex_shader_src, fragment_shader_src);
	
	GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;

	glGenVertexArrays(1, &vertex_array_object); // generate one vertex array object
	glGenBuffers(1, &vertex_buffer_object);		// generate one vertex buffer object
	glGenBuffers(1, &element_buffer_object);	// generate an element array buffer object

	glBindVertexArray(vertex_array_object);		// will bind all openGL calls related to vertex attributes to that array

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// upload loaded data to GPU
															//GL_STATIC_DRAW = opti to load once and use many times
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	while (!glfwWindowShouldClose(window)) { // making sure that the window should stay open unless closed
		
		// color of the background
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glUseProgram(shader_program); // activating shader program
		glBindVertexArray(vertex_array_object); // binding vao to tell openGL to use this specific one

		// drawing
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window); //swap to update each frame

		// handle at every loop cycle all events (closing window, resizing, etc..)
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);
	glDeleteBuffers(1, &element_buffer_object);
	glDeleteProgram(shader_program);

	glfwDestroyWindow(window);
	glfwTerminate();
	free(vertex_shader_src);
	free(fragment_shader_src);
	return (0);
}
