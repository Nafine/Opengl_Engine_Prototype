#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image/stbi_image.h>

#include <fstream>
#include <sstream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include "Texture.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void size_callback(GLFWwindow *window, int width, int height);

GLfloat vertices[] =
{	
//	 COORDINATES			COLORS					TEXTURE COORDINATES
	-0.5f, -0.5f, 0.0f,		0.3f, 0.4f, 0.10f,     0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,		0.4f, 0.9f, 0.80f,     2.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,		0.8f, 0.6f, 0.33f,     2.0f, 2.0f,
	-0.5f,  0.5f, 0.0f,		0.9f, 0.8f, 0.34f,     0.0f, 2.0f
};

GLuint indices[] =
{
	0, 1, 2, // right trianle
	0, 3, 2 // left triangle

	// 3 ______ 2
	//	|	  /|
	//	|    / |
	//	|   /  |
	//	|  /   |
	//	| /	   | 
	//	|/_____|
	//  0      1
};

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);

	if (in)
	{
		std::stringstream buf;

		buf << in.rdbuf();

		return buf.str();
	}
	throw(errno);
}

float transparency = 0.1;

float randColor = 1.2f;

bool reverse = false;

void changeColor()
{
	if (randColor >= 1) reverse = true;

	if (!reverse) randColor += (float)((std::rand() / ((RAND_MAX + 1u) / 100))) / 1000000;
	else
	{
		randColor -= (float)((std::rand() / ((RAND_MAX + 1u) / 100))) / 1000000;
		if (randColor <= 0) reverse = false;
	}
}


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "Dima gey", NULL, NULL);

	if (!window)
	{
		std::cerr << "can't create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, size_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

	std::string vertexCode = get_file_contents("../resources/shaders/default.vert");
	std::string fragmentCode = get_file_contents("../resources/shaders/default.frag");

	renderer::ShaderProgram defaultShader(vertexCode, fragmentCode);

	std::srand(std::time(NULL));

	{
		glViewport(0,0, width, height);

		renderer::VAO VAO;

		renderer::VBO VBO(sizeof(vertices), vertices, GL_STATIC_DRAW);

		renderer::Texture brickTex(GL_TEXTURE_2D);

		brickTex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		brickTex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		brickTex.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		brickTex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

		int width, height, channelsCount;

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load("../resources/textures/brick.png", &width, &height, &channelsCount, 0);

		if (data)
		{
			brickTex.init(GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		else
		{
			std::cerr << "Failed to load brick texture" << std::endl;
		}

		stbi_image_free(data);

		renderer::Texture massonTriangleTex(GL_TEXTURE_2D);

		massonTriangleTex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		massonTriangleTex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		massonTriangleTex.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		massonTriangleTex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

		data = stbi_load("../resources/textures/triangle.png", &width, &height, &channelsCount, 0);

		if (data)
		{
			massonTriangleTex.init(GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		else
		{
			std::cerr << "Failed to load masson texture" << std::endl;
		}

		renderer::EBO EBO(sizeof(indices), indices, GL_STATIC_DRAW);

		VAO.attachBuffer(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (GLvoid*)0);
		VAO.attachBuffer(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		VAO.attachBuffer(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

		VBO.unbind();

		defaultShader.use();

		glUniform1i(glGetUniformLocation(defaultShader.getShader(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(defaultShader.getShader(), "texture2"), 1);

		GLint transparencyLoc = glGetUniformLocation(defaultShader.getShader(), "transparency");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, brickTex.getTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, massonTriangleTex.getTexture());

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.5f, 0.7f, 0.6f, 1.0f);

			glClear(GL_COLOR_BUFFER_BIT);

			changeColor();

			//std::cout << randColor << '\n';

			glUniform1f(transparencyLoc, transparency);
			glUniform1f(glGetUniformLocation(defaultShader.getShader(), "randColor"), randColor);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
	{
		if (transparency < 1.0f) transparency += 0.01f;
	}

	else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
	{
		if (transparency > 0.0f) transparency -= 0.01f;
	}
}

void size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}