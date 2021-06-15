#ifndef THREEDEEMODELS
#define TRHEEDEEMODELS
#include <vector>
#include <fstream>

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


	Model(VertexData m_data, VertexLayout layout = VertexLayout::NORMAL);

	void render();

	~Model();
};

#endif