#pragma once

#include <glad/glad.h>
#include "VBO.h"

namespace renderer
{
	class VAO
	{
	public:

		VAO();

		~VAO();

		void bind();

		void unbind();

		void attachBuffer(VBO& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride,const void *pointer);

	private:
		GLuint m_ID;
	};
}
