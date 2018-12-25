/*
*	Written by:		Bassem Adas
*	Creation Date:  20/11/2018
*	Last Modified:	20/11/2018
*
*/


#pragma once
#include <GL/glew.h>
#include <string>
using namespace std;

GLuint createShader(const GLenum type, const string source);
GLuint createShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);

GLuint createBuffer(GLenum target, GLsizeiptr size, void * data, GLenum usage);