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

float vertices_quad[] = {
	-0.53f, -0.53f, 0.0f,
	 0.53f, -0.53f, 0.0f,
	 0.53f,  0.53f, 0.0f,
	-0.53f,  0.53f, 0.0f
};

float vertices_rectangle[] = {
	0.0f, -0.03f, 0.0f,
	0.5f,  0.0f,  0.0f,
	0.0f,  0.03f, 0.0f
};

float vertices_circle[360 * 3];

int clock_vbo(void)
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
	auto index = 0;
	for (auto i = 0; i < 360; i++)
	{
		const float degInRad = i* M_PI / 180.0f;
		vertices_circle[index++] = cos(degInRad)*radius;
		vertices_circle[index++] = sin(degInRad)*radius;
		vertices_circle[index++] = 0.0f;
	}


	GLuint vbo_quad;
	glGenBuffers(1, &vbo_quad);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertices_quad, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	GLuint vbo_circle;
	glGenBuffers(1, &vbo_circle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_circle);
	glBufferData(GL_ARRAY_BUFFER, 360 * 3 * sizeof(float), vertices_circle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	GLuint vbo_rectangle;
	glGenBuffers(1, &vbo_rectangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), vertices_rectangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);


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

			glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glDrawArrays(GL_QUADS, 0, 4);

			glBindBuffer(GL_ARRAY_BUFFER, vbo_circle);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glColor4f(0.38f, 0.38f, 0.38f, 1.0f);
			glDrawArrays(GL_POLYGON, 0, 360);
		}
		glPopMatrix();

		
		glRotatef(-6.0f, 0.0f, 0.0f, 1.0f);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glColor4f(0.24f, 0.24f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
			

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


