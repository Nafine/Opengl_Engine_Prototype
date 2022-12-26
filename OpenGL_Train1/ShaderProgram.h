#pragma once

#include <glad/glad.h>
#include <string>

namespace renderer
{
	class ShaderProgram
	{

	public:
		ShaderProgram(std::string& vertexCode, std::string& fragmentCode);

		~ShaderProgram();

		void use();

		GLuint getShader();

	private:

		GLuint m_ID;

		bool compileShaderErrors(GLuint shader);

		bool compileProgramErrors();

		bool compileShader(std::string& shaderCode, GLuint shaderID);
	};
}
