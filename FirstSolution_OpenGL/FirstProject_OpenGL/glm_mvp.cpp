/*
*	Written by:		Bassem Adas
*	Creation Date:  20/11/2018
*	Last Modified:	20/11/2018
*
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

int glm_mvp(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
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

	string vertexShaderSource =
								"#version 330 core\n"
								"layout (location = 0) in vec3 position;\n"
								"\n"
								"uniform mat4 view;\n"
								"uniform mat4 model;\n"
								"uniform mat4 projection;\n"
								"\n"
								"void main()\n"
								"{\n"
								"	gl_Position =  projection * view * model * vec4(position, 1.0f);\n"
								"}";

	string frag_Shader_Source =
								"#version 330 core\n"
								"out vec4 FragColor;\n"
								"void main()\n"
								"{\n"
								"	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
								"}";


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint VBO = createBuffer(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	GLuint vsId = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source);
	GLuint pId = createShaderProgram(vsId, fsId);
	
	glUseProgram(pId);

	
	//Transformation: Going 3D
	glm::mat4 model(1.0f);
	//model = rotate(model, radians(6.0f), vec3(1.0, 0.0, 0.0));

	glm::mat4 view(1.0f);
	view = translate(view, vec3(0.0f, -0.0f, -3.0f));
	
	GLuint viewLocation = glGetUniformLocation(pId, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

	glm::mat4 projection = perspective(radians(45.0f), (float)480 / (float)480, 0.1f, 11.0f);
	//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 100.0f);
	

	unsigned int projectionLocation = glGetUniformLocation(pId, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(10);
		//cout << "error0: " << glGetError() << endl;

		//glEnable(GL_DEPTH_TEST);
		model = rotate(model, glm::radians(6.0f), glm::vec3(1.0, 0.0, 1.0));
			
		unsigned int modelLocation = glGetUniformLocation(pId, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

