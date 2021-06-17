#ifndef THREEDEEMODELS
#define THREEDEEMODELS
#include <vector>
#include <fstream>
#include <core/texture.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexData
{
	std::vector<float> vertices;
	std::vector<unsigned int> indicies;
};

enum class VertexLayout
{
	NORMAL
};

class Model
{
private:
	unsigned int m_VAO, m_VBO, m_EBO;

	VertexData m_data;

public:

	unsigned int m_texID;


	Model(unsigned int texID, VertexData m_data, VertexLayout layout = VertexLayout::NORMAL);

	void render();

	~Model();
};

#endif