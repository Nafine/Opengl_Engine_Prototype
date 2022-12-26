#include "Texture.h"

namespace renderer
{
	Texture::Texture(GLenum textureType) : m_textureType(textureType)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(m_textureType, m_ID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture::init(GLint internalFormat, int width, int height, GLint border, GLint format, GLenum type, const void* data)
	{
		glTexImage2D(m_textureType, 0, internalFormat, width, height, border, format, type, data);
		glGenerateMipmap(m_textureType);
	}

	void Texture::setParameter(GLenum paramName, GLenum param)
	{
		glTexParameteri(m_textureType, paramName, param);
	}

	void Texture::bind()
	{
		glBindTexture(m_textureType, m_ID);
	}

	void Texture::unbind()
	{
		glBindTexture(m_textureType, 0);
	}

	GLuint Texture::getTexture()
	{
		return m_ID;
	}
}