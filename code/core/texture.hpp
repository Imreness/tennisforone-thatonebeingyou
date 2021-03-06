#ifndef TEXTUREOBJ
#define TEXTUREOBJ
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <fstream>

class Texture
{
private:

	//OpenGL ID
	unsigned int m_ID;

	//LoadOrder (0 - first texture, 1 - second texture, etc.)
	unsigned int m_loadOrder;

public:
	Texture(int width, int height, char* data, unsigned int loadOrder);

	void Use();

	~Texture();
};

#endif