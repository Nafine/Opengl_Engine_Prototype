#include "ShaderProgram.h"

#include <iostream>

namespace renderer
{
	ShaderProgram::ShaderProgram(std::string &vertexCode, std::string &fragmentCode)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (!compileShader(vertexCode, vertexShader))
		{
			std::cout << "Can't compile vertex shader" << std::endl;
			return;
		}

		if (!compileShader(fragmentCode, fragmentShader))
		{
			glDeleteShader(vertexShader);
			std::cout << "Can't compile fragment shader" << std::endl;
			return;
		}

		m_ID = glCreateProgram();

		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);

		glLinkProgram(m_ID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		if (compileProgramErrors())
		{
			glDeleteProgram(m_ID);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use()
	{
		glUseProgram(m_ID);
	}

	bool ShaderProgram::compileShader(std::string &shaderCode, GLuint shaderID)
	{
		const char* code = shaderCode.c_str();

		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		if (compileShaderErrors(shaderID))
		{
			return false;
		}

		return true;
	}

	bool ShaderProgram::compileShaderErrors(GLuint shader)
	{
		GLint compiled;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLchar infolog[1024];

			glGetShaderInfoLog(shader, 1024, nullptr, infolog);

			std::cerr << "Can't compile shader: \n" << infolog << std::endl;
			return true;
		}
		return false;
	}

	bool ShaderProgram::compileProgramErrors()
	{
		GLint compiled;

		glGetProgramiv(m_ID, GL_LINK_STATUS, &compiled);

		if (!compiled)
		{
			GLchar infolog[1024];

			glGetProgramInfoLog(m_ID, 1024, nullptr, infolog);

			std::cerr << "Can't link program: \n" << infolog << std::endl;

			return true;
		}

		return false;
	}

	GLuint ShaderProgram::getShader()
	{
		return m_ID;
	}

}
