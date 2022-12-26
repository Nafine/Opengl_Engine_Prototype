#include "VAO.h"

namespace renderer
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VAO::bind()
	{
		glBindVertexArray(m_ID);
	}

	void VAO::unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::attachBuffer(VBO &buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const void *pointer)
	{
		this->bind();
		buffer.bind();

		glVertexAttribPointer(layout, size, type, GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(layout);

		buffer.unbind();
	}
}
