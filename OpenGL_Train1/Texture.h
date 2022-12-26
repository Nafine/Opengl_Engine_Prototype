#pragma once

#include <glad/glad.h>

namespace renderer
{
	class Texture
	{
	public:

		Texture(GLenum textureType);

		~Texture();

		void init(GLint internalFormat, int width, int height, GLint border, GLint format, GLenum type, const void* data);

		void setParameter(GLenum paramName, GLenum param);

		void bind();

		void unbind();

		GLuint getTexture();

	private:

		GLuint m_ID;
		GLenum m_textureType;

	};
}
