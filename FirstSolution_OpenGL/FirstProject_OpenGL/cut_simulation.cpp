/*
*	Written by:		Bassem Adas
*	Creation Date:  20/11/2018
*	Last Modified:	20/11/2018
*
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iostream>
using namespace std;

//void eventHandler(GLFWwindow *window);




int cut_simulation(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(480, 480, "Simple Analog Clock", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(480, 480, "Simple Analog Clock", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glew error";
	}

	const float radius = 0.52f;
	float theta = 6.0f;
	float step = 1;
	bool swaped = false;
	int sign = 1;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(5);

		glPushMatrix();
		{
			//glLoadIdentity();

			glRotatef(-theta, 0.0f, 0.0f, 1.0f);
			glColor4f(0.24f, 0.24f, 0.0f, 1.0f); 
			glBegin(GL_TRIANGLES);
			{
				glVertex2f(-0.03f, -0.25f);
				glVertex2f(0.03f, -0.25f);
				//glVertex2f(0.03f, 0.7f);
				//glVertex2f(-0.03f, 0.7f);
				glVertex2f(0.0f, 0.7f);
			}
			glEnd();

			if (theta >= 50 && !swaped) {
				step = -step;
				swaped = !swaped;
				cout << "in swaped" << endl;
			}else
				if (theta <= 5 && swaped)
				{
					step = -step;
					swaped = !swaped;
					cout << "re swaped" << endl;
				}
			theta += step;
		
			
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotatef(theta, 0.0f, 0.0f, 1.0f);
			glColor4f(0.38f, 0.38f, 0.38f, 1.0f);
			glBegin(GL_TRIANGLES);
			{
				glVertex2f(-0.03f, -0.25f);
				glVertex2f(0.03f, -0.25f);
				//glVertex2f(0.03f, 0.7f);
				//glVertex2f(-0.03f, 0.7f);
				glVertex2f(0.03f, 0.7f);
			}
			glEnd();

		}
		glPopMatrix();
	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		//eventHandler(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



