#ifndef SHADERHEADER
#define SHADERHEADER
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <string_view>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	//OpenGL ID
	unsigned int m_ID;

	void CheckError(unsigned int ID, bool isProgram);

public:

	//DEBUG - Generate shader program from file without geometry shader
	Shader(const std::string_view vertexPath, const std::string_view fragmentPath);

	//DEBUG - Generate shader program from file with geometry shader
	Shader(const std::string_view vertexPath, const std::string_view fragmentPath, const std::string_view geometryPath);

	//TODO - Implement loading from strings

	~Shader();

	void Use();

	//Setting values (Matrixes , vectors , texture ID's etc.)
	void setUniform(const char* name, glm::mat4& value);
	void setUniform(const char* name, glm::mat3& value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float value);
	void setUniform(const char* name, glm::vec4 value);
	void setUniform(const char* name, glm::vec3 value);
	void setUniform(const char* name, glm::vec2 value);
	void setUniform(const char* name, float* mat4value);
};

#endif