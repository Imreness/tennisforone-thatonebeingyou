#include <core/shader.hpp>

void Shader::CheckError(unsigned int ID, bool isProgram)
{
	int success;
	char infolog[1024];

	if (isProgram)
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 1024, NULL, infolog);
			spdlog::error("Couldn't link shader program. {}", infolog);
			std::this_thread::sleep_for(std::chrono::seconds(2));
			abort();
		}


	}
	else
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, infolog);
			spdlog::error("Couldn't compile shader program. {}", infolog);
			std::this_thread::sleep_for(std::chrono::seconds(2));
			abort();
		}
	}
}

Shader::Shader(const std::string_view vertexPath, const std::string_view fragmentPath)
{
	spdlog::warn("Loading shader from file, make sure this is a debug build. Shader locations: {} ; {}",
		vertexPath.data(), fragmentPath.data());
	spdlog::debug("Loading shader from file: {} ; {}", vertexPath.data(), fragmentPath.data());

	//Load Shader from file
	std::ifstream      vertexFile  , fragmentFile  ;
	std::string  	   vertexString, fragmentString;

	vertexFile.open(vertexPath.data());
	fragmentFile.open(fragmentPath.data());


	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream vertexSstream, fragmentSstream;

		vertexSstream << vertexFile.rdbuf();
		fragmentSstream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexString = vertexSstream.str();
		fragmentString = fragmentSstream.str();
	}
	catch (std::ifstream::failure& e)
	{
		spdlog::error("Failed to load shader. Shaders: {} ; {}", vertexPath.data(), fragmentPath.data());
		std::this_thread::sleep_for(std::chrono::seconds(2));
		abort();
	}
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	CheckError(vertex, false);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	CheckError(fragment, false);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	CheckError(m_ID, true);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const std::string_view vertexPath, const std::string_view fragmentPath, const std::string_view geometryPath)
{
	spdlog::warn("Loading shader from file, make sure this is a debug build. Shader locations: {} ; {}",
		vertexPath.data(), fragmentPath.data());
	spdlog::debug("Loading shader from file: {} ; {}", vertexPath.data(), fragmentPath.data());

	//Load Shader from file
	std::ifstream vertexFile, fragmentFile, geometryFile;
	std::string   vertexString, fragmentString, geometryString;

	vertexFile.open(vertexPath.data());
	
	fragmentFile.open(fragmentPath.data());
	geometryFile.open(geometryPath.data());

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream vertexSstream, fragmentSstream, geometrySstream;

		vertexSstream << vertexFile.rdbuf();
		fragmentSstream << fragmentFile.rdbuf();
		geometrySstream << geometryFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();
		geometryFile.close();

		vertexString = vertexSstream.str();
		fragmentString = fragmentSstream.str();
		geometryString = geometrySstream.str();
	}
	catch (std::ifstream::failure& e)
	{
		spdlog::error("Failed to load shader. Shaders: {} ; {}", vertexPath.data(), fragmentPath.data());
		std::this_thread::sleep_for(std::chrono::seconds(2));
		abort();
	}
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	const char* geometryCode = geometryString.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	CheckError(vertex, false);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	CheckError(fragment, false);

	unsigned int geometry = glCreateShader(GL_GEOMETRY_SHADER);

	glShaderSource(geometry, 1, &geometryCode, NULL);
	glCompileShader(geometry);
	CheckError(geometry, false);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glAttachShader(m_ID, geometry);
	glLinkProgram(m_ID);
	CheckError(m_ID, true);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);
}

Shader::~Shader()
{
	spdlog::debug("Deleting shader");
	glDeleteShader(m_ID);
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

void Shader::setUniform(const char* name, glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, &value[0][0]);
}
void Shader::setUniform(const char* name, glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, false, &value[0][0]);
}
void Shader::setUniform(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::setUniform(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void Shader::setUniform(const char* name, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}
void Shader::setUniform(const char* name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}
void Shader::setUniform(const char* name, glm::vec2 value)
{
	glUniform2fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}
void Shader::setUniform(const char* name, float* mat4value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, &mat4value[0]);
}
