/*
*	Written by:		Bassem Adas
*	Creation Date:  10/11/2018
*	Last Modified:	10/11/2018
*
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float vertices[(7 + 360) * 3] = {
	-0.53f, -0.53f, 0.0f,
	 0.53f, -0.53f, 0.0f,
	 0.53f,  0.53f, 0.0f,
	-0.53f,  0.53f, 0.0f,

	0.0f, -0.03f, 0.0f,
	0.5f,  0.0f,  0.0f,
	0.0f,  0.03f, 0.0f
};

GLuint idx_quad[] = {
	0, 1, 2, 3
};


GLuint idx_rectangle[] = {
	4 ,5 ,6
};

GLuint idx_circle[360];

int clock_indices(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 480, "Simple Analog Clock", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glew error";
	}

	const auto radius = 0.52f;
	auto index = 7 * 3;
	for (auto i = 0; i < 360; i++)
	{
		const float degInRad = i* M_PI / 180.0f;
		vertices[index++] = cos(degInRad)*radius;
		vertices[index++] = sin(degInRad)*radius;
		vertices[index++] = 0.0f;
	}

	for (auto i = 0; i < 360; i++)
	{
		idx_circle[i] = i + 7;
	}


	GLuint vbo_all_vertices;
	glGenBuffers(1, &vbo_all_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_all_vertices);
	glBufferData(GL_ARRAY_BUFFER, (7 + 360) * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	GLuint ibo_quad;
	glGenBuffers(1, &ibo_quad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_quad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), idx_quad, GL_STATIC_DRAW);

	GLuint ibo_rectangle;
	glGenBuffers(1, &ibo_rectangle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_rectangle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), idx_rectangle, GL_STATIC_DRAW);

	GLuint ibo_circle;
	glGenBuffers(1, &ibo_circle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_circle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 360 * sizeof(GLuint), idx_circle, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(60);

		glPushMatrix();
		{
			glLoadIdentity();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_quad);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_circle);
			glColor4f(0.38f, 0.38f, 0.38f, 1.0f);
			glDrawElements(GL_POLYGON, 360, GL_UNSIGNED_INT, NULL);
		}
		glPopMatrix();

		glRotatef(-6.0f, 0.0f, 0.0f, 1.0f);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_rectangle);
		glColor4f(0.24f, 0.24f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


