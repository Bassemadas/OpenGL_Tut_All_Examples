/*
*	Written by:		Bassem Adas
*	Creation Date:  5/12/2018
*	Last Modified:	5/12/2018
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace glm;

int texture_sample1(void)
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
		"layout (location = 1) in vec3 vertexColor;\n"
		"layout (location = 2) in vec2 vertexTexture;\n"
		"out vec3 color;\n"
		"out vec2 TexCoord;\n"
		"\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position =  projection * view * model * vec4(position, 1.0f);\n"
		"	color = vertexColor;\n"
		"	TexCoord = vertexTexture;\n"
		"}";

	string frag_Shader_Source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(ourTexture, TexCoord);\n"
		//"	FragColor = texture(ourTexture, TexCoord) * vec4(color, 1.0);\n"
		"}";

	
	float vertices[] = {
		 // positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO = createBuffer(GL_ARRAY_BUFFER, 4 * 8 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	GLuint vsId = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source);
	GLuint pId = createShaderProgram(vsId, fsId);

	glUseProgram(pId);

	
	// load and create a texture 
	// -------------------------------------------------------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//string textureFilePath = "resources/textures/container.jpg";
	string textureFilePath = "resources/textures/textures_exercise2.png";
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(textureFilePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);

	//Transformation: Going 3D
	// -------------------------------------------------------------------------
	glm::mat4 model(1.0f);

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
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_QUADS, 0, 4);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

