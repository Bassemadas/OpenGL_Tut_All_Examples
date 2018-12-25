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

void eventHandler(GLFWwindow *window);

int vw = 480;
int vh = 480;
int h = 800;
int w = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	int x0 = 0;
	int y0 = 0;
	if (width > vw)
		x0 = (width - vw) / 2;
	else vw = width;
	if (height > vh)
		y0 = (height - vh) / 2;
	else vh = height;

	
	glViewport(x0, y0, vw, vh);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		cout << "released " << endl;
}


int clock(void)
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glew error";
	}

	const float radius = 0.52f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(60);

		glPushMatrix();
		{
			glLoadIdentity();
		
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glBegin(GL_QUADS);
			{
				glVertex2f(-0.53f, -0.53f);
				glVertex2f(0.53f, -0.53f);
				glVertex2f(0.53f, 0.53f);
				glVertex2f(-0.53f, 0.53f);
			}
			glEnd();

			glColor4f(0.38f, 0.38f, 0.38f, 1.0f);
			glBegin(GL_POLYGON);
			{
				for (auto i = 0; i < 360; i++)
				{
					float degInRad = i* M_PI / 180.0f;
					glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
				}
			}
			glEnd();

			//glBegin(GL_TRIANGLE_FAN);
			//{
			//	glVertex2f(0, 0);
			//	for (auto i = 0; i < 360; i++)
			//	{
			//		float degInRad = i* M_PI / 180.0f;
			//		glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
			//	}
			//	glVertex2f(0, 0.5f);
			//}
			//glEnd();

			//glBegin(GL_LINE_LOOP);
			//{
			//	for (auto i = 0; i < 360; i++)
			//	{
			//		float degInRad = i* M_PI / 180.0f;
			//		glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
			//	}
			//}
			//glEnd();

			//glColor4f(1.0, 1.0, 0.0, 1.0);
			//glPointSize(3.0f);
			//float r1 = 0.509;
			//glBegin(GL_POINTS);
			//{
			//	for (auto i = 0; i < 60; i++)
			//	{
			//		float degInRad = (i * 6) * M_PI / 180.0f;
			//		glVertex2f(cos(degInRad)*r1, sin(degInRad)*r1);
			//	}
			//}
			//glEnd();
		}
		glPopMatrix();

		
		glRotatef(-6.0f, 0.0f, 0.0f, 1.0f);

		glColor4f(0.24f, 0.24f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(0.0f, -0.03f);
			glVertex2f(0.5f, 0.0f);
			glVertex2f(0.0f, 0.03f);
		}
		glEnd();
		

	/*	glBegin(GL_LINE_LOOP);
		glVertex2f(-1, -1);
		glVertex2f(-1, 1);
		glVertex2f(1, 1);
		glVertex2f(1, -1);
		glEnd();*/
		

		;
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		eventHandler(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



void eventHandler(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		cout << "Mouse Left Released" << endl;
	}*/
}