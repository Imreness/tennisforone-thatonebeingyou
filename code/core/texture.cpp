#include <core/texture.hpp>
#include <fstream>
#include <vector>

Texture::Texture(int width, int height, char* data, unsigned int loadOrder = 0)
	: m_loadOrder(loadOrder)
{
	glGenTextures(1, &m_ID);

	spdlog::debug("Loading texture with resolution of: {}x{}", width, height);

	//Create texture
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);



	//Set parameters
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, fLargest);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] data;
}

void Texture::Use()
{
	//With the '33984' offset, we can set all the textures that we want! 
	//33984 in OpenGL's ENUM is GL_TEXTURE0
	glActiveTexture((GLenum)(33984 + m_loadOrder));
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

Texture::~Texture(){
	spdlog::debug("Deleting Texture...");
	glDeleteTextures(1 , &m_ID);
}