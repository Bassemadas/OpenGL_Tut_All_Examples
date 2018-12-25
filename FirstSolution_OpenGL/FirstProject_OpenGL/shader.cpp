/*
*	Written by:		Bassem Adas
*	Creation Date:  15/10/2018
*	Last Modified:	15/10/2018
*
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
using namespace std;

int shader(void)
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

	string vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
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

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	GLuint vsId= glCreateShader(GL_VERTEX_SHADER);
	GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);


	const GLchar * c1 = vertexShaderSource.c_str();
	glShaderSource(vsId, 1, &c1, NULL);
	const GLchar * c2 = frag_Shader_Source.c_str();
	glShaderSource(fsId, 1, &c2, NULL);

	glCompileShader(vsId);
	int  success;
	char infoLog[512];
	glGetShaderiv(vsId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vsId, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fsId);
	char infoLog1[512];
	glGetShaderiv(fsId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fsId, 512, NULL, infoLog1);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog1 << std::endl;
	}

	GLuint pId = glCreateProgram();
	glAttachShader(pId, vsId);
	glAttachShader(pId, fsId);

	glLinkProgram(pId);

	glUseProgram(pId);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


