#include <core/model.hpp>

Model::Model(unsigned int texID,VertexData data, glm::mat4 initTransform, VertexLayout layout) :
	m_texID{texID},m_data{std::move(data)}, m_initTransform{initTransform} 
{
	//This debug log is probably useless. But I figured IF i wanted to make sure that the object is FREED up, I should make
	//sure that the object is also reserved. Bad part is, I cannot specify WHICH model object is being created...
	spdlog::debug("Creating model object...");
	glCreateBuffers(1, &m_VBO);
	glCreateBuffers(1, &m_EBO);

	glCreateVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_data.vertices.size() * sizeof(float), &m_data.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.indicies.size() * sizeof(unsigned int), &m_data.indicies[0], GL_STATIC_DRAW);

	switch(layout)
	{
		case VertexLayout::NORMAL:
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
			break;
	}
}

void Model::render()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_data.indicies.size(), GL_UNSIGNED_INT, 0);
}

Model::~Model(){
	spdlog::debug("Deleting model object...");
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);

	glDeleteVertexArrays(1, &m_VAO);
}