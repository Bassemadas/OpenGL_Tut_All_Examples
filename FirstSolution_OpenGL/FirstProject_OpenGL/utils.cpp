/*
*	Written by:		Bassem Adas
*	Creation Date:  20/11/2018
*	Last Modified:	20/11/2018
*
*/


#include <GL/glew.h>
#include <string>
#include <iostream>
using namespace std;

GLuint createShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	GLuint pId = glCreateProgram();
	glAttachShader(pId, vertexShaderId);
	glAttachShader(pId, fragmentShaderId);
	glLinkProgram(pId);

	//check for errors
	int  success;
	char infoLog[512];
	glGetProgramiv(pId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(pId, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	}
	return pId;
}

GLuint createShader(const GLenum type, const string source)
{
	const GLchar * c = source.c_str();

	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &c, NULL);
	glCompileShader(shaderId);

	//check for errors
	int  success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		if (type == GL_VERTEX_SHADER)
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		else
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	return shaderId;
}

GLuint createBuffer(GLenum target, GLsizeiptr size, void * data, GLenum usage )
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(target, size, data, usage);
	return VBO;
}