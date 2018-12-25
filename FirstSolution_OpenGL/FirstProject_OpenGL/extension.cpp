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

int extension(void)
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
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	const GLubyte * s = glGetString(GL_VERSION);
	cout << "OpenGL Version:" << s << endl;

	cin.get();

	glfwTerminate();
	return 0;
}
