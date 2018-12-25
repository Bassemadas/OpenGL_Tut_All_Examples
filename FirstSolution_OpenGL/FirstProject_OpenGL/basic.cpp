/*
*	Written by:		Bassem Adas
*	Creation Date:  10/10/2018
*	Last Modified:	10/10/2018
*
*/

#include <GLFW/glfw3.h>

int basic(void)
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


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//int w, h;
		//glfwGetFramebufferSize(window, &w, &h);
		//glViewport(0, 0, w, h);
		//glViewport(0, 0, 100, 100);
		//glShadeModel(GL_FLAT);
		//glShadeModel(GL_SMOOTH);
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex2f(0.5f, 0.5f);
		//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glVertex2f(-0.5f, 0.5f);
		glEnd();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
