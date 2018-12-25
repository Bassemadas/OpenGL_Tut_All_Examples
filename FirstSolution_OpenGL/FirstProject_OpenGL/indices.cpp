/*
*	Written by:		Bassem Adas
*	Creation Date:  15/10/2018
*	Last Modified:	15/10/2018
*
*/



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int indicesBuffer(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glew error";
	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	//0
		 0.5f, -0.5f, 0.0f,	//1
		 0.5f,  0.5f, 0.0f,	//2
		 0.0f,  1.0f, 0.0f,	//3
		-0.5f,  0.5f, 0.0f	//4
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 4,
		2, 4, 0
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 5 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//glRotatef(6.0f, 0.0f, 0.0f, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
