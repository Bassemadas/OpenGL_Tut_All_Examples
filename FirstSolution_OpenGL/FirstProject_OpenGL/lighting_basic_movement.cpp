/*
*	Written by:		Bassem Adas
*	Creation Date:  12/12/2018
*	Last Modified:	15/12/2018
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

int lighting_basic_movement(void)
{
	#pragma region Window and GL Initialization
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
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
	#pragma endregion Window and GL Initialization

	//--------------------------------------- The Object Cube Shaders Source-------------------------
	#pragma region The Object Cube Shaders Source
	string vertexShaderSource =
							"#version 330 core\n"
							"layout (location = 0) in vec3 position;\n"
							"layout (location = 1) in vec3 aNormal;\n"
							"out vec3 FragPos;\n"
							"out vec3 Normal;\n"
							"\n"
							"uniform mat4 view;\n"
							"uniform mat4 model;\n"
							"uniform mat4 projection;\n"
							"\n"
							"void main()\n"
							"{\n"
							"	FragPos = vec3(model * vec4(position, 1.0));\n"
							"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
							"	gl_Position = projection * view * vec4(FragPos, 1.0);\n"
							"}";

	string frag_Shader_Source =
							"#version 330 core\n"
							"out vec4 FragColor;\n"
							"in vec3 Normal;\n"
							"in vec3 FragPos;\n"
							"uniform vec3 viewPos;\n"
							"uniform vec3 lightPos;\n"
							"uniform vec3 objectColor;\n"
							"uniform vec3 lightColor;\n"
							"void main()\n"
							"{\n"
							"	// ambient\n"
							"	float ambientStrength = 0.1;\n"
							"	vec3 ambient = ambientStrength * lightColor;\n"
							"	\n"
							"	// diffuse \n"
							"	vec3 norm = normalize(Normal);\n"
							"	vec3 lightDir = normalize(lightPos - FragPos);\n"
							"	float diff = max(dot(norm, lightDir), 0.0);\n"
							"	vec3 diffuse = diff * lightColor;\n"
							"	// specular\n"
							"	float specularStrength = 0.5;\n"
							"	vec3 viewDir = normalize(viewPos - FragPos);\n"
							"	vec3 reflectDir = reflect(-lightDir, norm);\n"
							"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
							"	vec3 specular = specularStrength * spec * lightColor;\n"
							"	vec3 result = (ambient + diffuse + specular) * objectColor;\n"
							//"	discard;"
							"	FragColor = vec4(result, 1.0);\n"
							"}";

	#pragma endregion The Object Cube Shaders Source

	//--------------------------------------- The Lamp Cube Shaders Source-------------------------
	#pragma region The Lamp Cube Shaders Source
	string light_VertexShaderSource =
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

	string light_Frag_Shader_Source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f);\n"
		"}";
	#pragma endregion The Lamp Cube Shaders Source

	//-----------------------------------------------------------------------------------
	#pragma region Vertices and vertex buffer objects
	float vertices[] = {
		//Positions						//Normal	
		-0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f
	};


	//both object and light are cubes share the same buffer
	GLuint VBO = createBuffer(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//--------------------------------------- The Object Cube Attributes-------------------------
	GLuint cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//--------------------------------------- The Lamp Cube Attributes-------------------------
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	#pragma endregion Vertices and vertex buffer objects

	#pragma region Shaders
	//--------------------------------------- The Object Cube Shader Program-------------------------
	GLuint object_vsId = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint object_fsId = createShader(GL_FRAGMENT_SHADER, frag_Shader_Source);
	GLuint object_pId = createShaderProgram(object_vsId, object_fsId);


	//--------------------------------------- The Lamp Cube Shader Program-------------------------
	GLuint light_vsId = createShader(GL_VERTEX_SHADER, light_VertexShaderSource);
	GLuint light_fsId = createShader(GL_FRAGMENT_SHADER, light_Frag_Shader_Source);
	GLuint light_pId = createShaderProgram(light_vsId, light_fsId);
	#pragma endregion Shaders

	glEnable(GL_DEPTH_TEST);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(10);
		//cout << "error0: " << glGetError() << endl;

		//float lightX = 2.0f * sin(glfwGetTime());
		float lightX = sin(glfwGetTime());
		float lightY = -0.3f;
		//float lightZ = 1.5f * cos(glfwGetTime());
		float lightZ = cos(glfwGetTime());
		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
		//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		//--------------------------------------- The Object Cube ----------------------------
		#pragma region The Object Cube
		glUseProgram(object_pId);

		glm::mat4 projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		unsigned int projectionLocation = glGetUniformLocation(object_pId, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

		glm::mat4 view(1.0f);
		glm::vec3 viewPos(0.0f, 0.0f, 3.0);
		view = glm::lookAt(viewPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		//view = translate(view, vec3(0.0f, 0.0f, -5.0f));
		unsigned int viewLocation = glGetUniformLocation(object_pId, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		unsigned int modelLocation = glGetUniformLocation(object_pId, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		GLuint lightColorLocation = glGetUniformLocation(object_pId, "lightColor");
		glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
		GLuint objectColorLocation = glGetUniformLocation(object_pId, "objectColor");
		glUniform3f(objectColorLocation, 1.0f, 0.5f, 0.31f);
		GLuint lightPosLocation = glGetUniformLocation(object_pId, "lightPos");
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));

		GLuint viewPossLocation = glGetUniformLocation(object_pId, "viewPos");
		glUniform3fv(viewPossLocation, 1, glm::value_ptr(viewPos));

		// render the object
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		#pragma endregion The Object Cube

		//--------------------------------------- The Lamp Cube-------------------------
		#pragma region The Lamp Cube
		glUseProgram(light_pId);
		unsigned int projectionLocation_light = glGetUniformLocation(light_pId, "projection");
		glUniformMatrix4fv(projectionLocation_light, 1, GL_FALSE, value_ptr(projection));
		unsigned int viewLocation_light = glGetUniformLocation(light_pId, "view");
		glUniformMatrix4fv(viewLocation_light, 1, GL_FALSE, value_ptr(view));

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		unsigned int modelLocation_light = glGetUniformLocation(light_pId, "model");
		glUniformMatrix4fv(modelLocation_light, 1, GL_FALSE, value_ptr(model));

		// render the light
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		#pragma endregion  The Lamp Cube

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

