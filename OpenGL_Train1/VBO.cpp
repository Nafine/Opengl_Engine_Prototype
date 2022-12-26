#include "VBO.h"

namespace renderer
{
	VBO::VBO(GLsizeiptr size, const void* data, GLenum usage) : m_usage(usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, m_usage);
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void VBO::update(GLsizeiptr size, const void *data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, m_usage);
	}

	void VBO::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VBO::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

