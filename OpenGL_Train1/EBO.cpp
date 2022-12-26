#include "EBO.h"

namespace renderer
{
	EBO::EBO(GLsizeiptr size, const void* data, GLenum usage) : m_usage(usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, m_usage);
	}

	EBO::~EBO()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void EBO::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void EBO::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
