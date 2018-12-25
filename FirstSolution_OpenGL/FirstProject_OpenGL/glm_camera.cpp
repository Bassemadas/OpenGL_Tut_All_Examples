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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -10.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float fov = 45.0f;// field of view
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

int firstMouse = 1;
int lastX = 400;
int lastY = 300;
float pitch1 = 0.0f;
float yaw1 = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw1 += xoffset;
	pitch1 += yoffset;
	if (pitch1 > 89.0f)
		pitch1 = 89.0f;
	if (pitch1 < -89.0f)
		pitch1 = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw1)) * cos(glm::radians(pitch1));
	front.y = sin(glm::radians(pitch1));
	front.z = sin(glm::radians(yaw1)) * cos(glm::radians(pitch1));
	cameraFront = glm::normalize(front);
}

int glm_camera(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetScrollCallback(window, scroll_callback);

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
		"layout (location = 1) in vec3 vertexColor;\n"
		"out vec3 color;\n"
		"\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position =  projection * view * model * vec4(position, 1.0f);\n"
		"	color = vertexColor;\n"
		"}";

	string frag_Shader_Source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(color, 1.0f);\n"
		"}";


	float vertices[] = {
		//Positions						//Colors
		-0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f,  0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f,  0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		-0.5f,  0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		-0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,

		-0.5f, -0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,
		 0.5f, -0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,
		 0.5f,  0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,
		 0.5f,  0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,
		-0.5f,  0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,
		-0.5f, -0.5f,  0.5f,			 0.24f, 0.24f, 0.0f,

		-0.5f,  0.5f,  0.5f,			 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,			 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,			 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,			 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,			 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,			 1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,			 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,			 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,			 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,			 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,			 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,			 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f, -0.5f,  0.5f,			 0.38f, 0.38f, 0.38f,
		 0.5f, -0.5f,  0.5f,			 0.38f, 0.38f, 0.38f,
		-0.5f, -0.5f,  0.5f,			 0.38f, 0.38f, 0.38f,
		-0.5f, -0.5f, -0.5f,			 0.38f, 0.38f, 0.38f,

		-0.5f,  0.5f, -0.5f,			 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,			 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,			 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,			 0.0f, 0.0f, 1.0f,
	};

	GLuint VBO = createBuffer(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	GLuint vsId = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source);
	GLuint pId = createShaderProgram(vsId, fsId);

	
	glUseProgram(pId);


	//Transformation: Going 3D	
	//glm::mat4 projection = perspective(radians(45.0f), (float)1024 / (float)768, 0.1f, 10.0f);
	//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 100.0f);

	


	glm::mat4 view(1.0f);
	view = translate(view, vec3(0.0f, -0.0f, -3.0f));

	unsigned int viewLocation = glGetUniformLocation(pId, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));


	glm::mat4 model(1.0f);

	glEnable(GL_DEPTH_TEST);
	//glfwSetScrollCallback(window, scroll_callback);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(10);
		//cout << "error0: " << glGetError() << endl;
		
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		//view = glm::lookAt(
		//	glm::vec3(camX, 0.0, camZ),  //Camera poistion = eye
		//	glm::vec3(0.0, 0.0, 0.0),	 //Camera Target = 
		//	glm::vec3(0.0, 1.0, 0.0)	 //Up
		//);
		

		float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

		glm::mat4 projection = perspective(fov, (float)1024 / (float)768, 0.1f, 10.0f);
		unsigned int projectionLocation = glGetUniformLocation(pId, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		unsigned int modelLocation = glGetUniformLocation(pId, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

