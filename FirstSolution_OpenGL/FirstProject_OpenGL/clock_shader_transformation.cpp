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


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include "utils.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//(Quad + Triangle + Circle) * (Coordinates + Color)
float vertices_and_color_trans[(4 + 3 + 360) * (3 + 3)] = {
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


string vertexShaderSourceTransformation =
									"#version 330 core\n"
									"layout (location = 0) in vec3 position;\n"
									"layout (location = 1) in vec3 vertexColor;\n"
									"out vec3 color;\n"
									"uniform mat4 trans;\n"
									"void main()\n"
									"{\n"
									"	gl_Position = trans * vec4(position.x, position.y, position.z, 1.0f);\n"
									"	color = vertexColor;\n"
									"}";

string frag_Shader_Source_transformation =
									"#version 330 core\n"
									"out vec4 FragColor;\n"
									"in vec3 color;\n"
									"void main()\n"
									"{\n"
									"	FragColor = vec4(color, 1.0f);\n"
									"}";



int clock_shader_transformation(void)
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
		vertices_and_color_trans[index++] = cos(degInRad) * radius;	//x
		vertices_and_color_trans[index++] = sin(degInRad) * radius;	//y
		vertices_and_color_trans[index++] = 0.0f;					//z

		//Color
		vertices_and_color_trans[index++] = 0.38f;	//R
		vertices_and_color_trans[index++] = 0.38f;	//G
		vertices_and_color_trans[index++] = 0.38f;	//B
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint vbo_quad = createBuffer(GL_ARRAY_BUFFER, (4 + 3 + 360) * (3 + 3) * sizeof(GLfloat),
		vertices_and_color_trans, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint vsId = createShader(GL_VERTEX_SHADER, vertexShaderSourceTransformation);
	GLuint fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source_transformation);
	GLuint pId = createShaderProgram(vsId, fsId);
	glUseProgram(pId);


	glm::mat4 animated_object_model(1.0f);
	glm::mat4 static_objects_model(1.0f);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(60);

		GLuint transLocation = glGetUniformLocation(pId, "trans");

		glUniformMatrix4fv(transLocation, 1, GL_FALSE, value_ptr(static_objects_model));
		glDrawArrays(GL_QUADS, 0, 4);
		glDrawArrays(GL_POLYGON, 7, 360);

		animated_object_model = glm::rotate(animated_object_model, glm::radians(-6.0f), glm::vec3(0.0, 0.0, 1.0));
		glUniformMatrix4fv(transLocation, 1, GL_FALSE, value_ptr(animated_object_model));
		glDrawArrays(GL_TRIANGLES, 4, 3);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

