#pragma once

#include <glad/glad.h>

namespace renderer
{
	class EBO 
	{
	public:

		EBO(GLsizeiptr size, const void *data, GLenum usage);

		~EBO();

		void bind();

		void unbind();

	private:
		GLenum m_usage;
		GLuint m_ID;
	};
}
