#pragma once

#include <glad/glad.h>

namespace renderer
{
	class VBO
	{
	public:

		VBO(GLsizeiptr size, const void* data, GLenum usage);

		~VBO();

		void update(GLsizeiptr size, const void* data);

		void bind();

		void unbind();

	private:
		GLenum m_usage;
		GLuint m_ID;
	};

}
