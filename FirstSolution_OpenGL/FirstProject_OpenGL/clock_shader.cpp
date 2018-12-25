/*
*	Written by:		Bassem Adas
*	Creation Date:  10/11/2018
*	Last Modified:	20/11/2018
*
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include "utils.h"
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//(Quad + Triangle + Circle) * (Coordinates + Color)
float vertices_and_color[(4 + 3 + 360) * (3 + 3)] = {
	//Vertex Attribute 0		//Vertex Attribute 1
	//Coordinates (x, y, z)		//Color (R, G, B)
	-0.53f, -0.53f, 0.0f,		1.0f, 1.0f, 1.0f,
	 0.53f, -0.53f, 0.0f,		1.0f, 1.0f, 1.0f,
	 0.53f,  0.53f, 0.0f,		1.0f, 1.0f, 1.0f,
	-0.53f,  0.53f, 0.0f,		1.0f, 1.0f, 1.0f,

	 0.0f, -0.03f, 0.0f,		0.24f, 0.24f, 0.0f,
	 0.5f,  0.0f,  0.0f,		0.24f, 0.24f, 0.0f,
	 0.0f,  0.03f, 0.0f,		0.24f, 0.24f, 0.0f
};


string vertexShaderSource1 =
							"#version 330 core\n"
							"layout (location = 0) in vec3 position;\n"
							"layout (location = 1) in vec3 vertexColor;\n"
							"out vec3 color;\n"
							"void main()\n"
							"{\n"
							"	gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
							"	color = vertexColor;\n"
							"}";

string frag_Shader_Source1 =
							"#version 330 core\n"
							"out vec4 FragColor;\n"
							"in vec3 color;\n"
							"void main()\n"
							"{\n"
							"	FragColor = vec4(color, 1.0f);\n"
							"}";



int clock_shader(void)
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
	auto index = (4 + 3) * (3 + 3);
	for (auto i = 0; i < 360; i++)
	{
		//Coordinates
		const float degInRad = i* M_PI / 180.0f;
		vertices_and_color[index++] = cos(degInRad) * radius; //x
		vertices_and_color[index++] = sin(degInRad) * radius; //y
		vertices_and_color[index++] = 0.0f;					  //z

		//Color
		vertices_and_color[index++] = 0.38f;	//R
		vertices_and_color[index++] = 0.38f;	//G
		vertices_and_color[index++] = 0.38f;	//B
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint vbo_quad = createBuffer(GL_ARRAY_BUFFER, (4 + 3 + 360) * (3 + 3) * sizeof(GLfloat), 
		vertices_and_color, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint vsId = createShader(GL_VERTEX_SHADER, vertexShaderSource1);
	GLuint fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source1);
	GLuint pId = createShaderProgram(vsId, fsId);
	glUseProgram(pId);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(60);

		glDrawArrays(GL_QUADS, 0, 4);
		glDrawArrays(GL_POLYGON, 7, 360);
		glDrawArrays(GL_TRIANGLES, 4, 3);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

