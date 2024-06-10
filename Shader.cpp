#include "Shader.hpp"
#include "logger.hpp"

Shader::Shader(const std::string &vsh, const std::string &fsh) : id(glCreateProgram()) {
	unsigned int vertex, fragment;
	int status;
	char infoLog[512];

	const char* vCode = vsh.c_str();
	const char* fCode = fsh.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::string error = infoLog;
		Logger::log(Logger::ERROR, "Shader", "Failed to compile vertex shader due to error: " + error);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::string error = infoLog;
		Logger::log(Logger::ERROR, "Shader", "Failed to compile fragment shader due to error: " + error);
	}

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetShaderiv(id, GL_LINK_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::string error = infoLog;
		Logger::log(Logger::ERROR, "Shader", "Failed to link shader program due to error: " + error);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const {
	glUseProgram(id);
}

void Shader::setBool(const std::string &loc, bool val) const {
	glUniform1i(glGetUniformLocation(id, loc.c_str()), (int)val);
}

void Shader::setInt(const std::string &loc, int val) const {
	glUniform1i(glGetUniformLocation(id, loc.c_str()), val);
}

void Shader::setFloat(const std::string &loc, float val) const {
	glUniform1f(glGetUniformLocation(id, loc.c_str()), val);
}

void Shader::setVec3f(const std::string &loc, glm::vec3 val) const {
	glUniform3f(glGetUniformLocation(id, loc.c_str()), val.x, val.y, val.z);
}

void Shader::setMat4f(const std::string &loc, glm::mat4 val) const {
	glUniformMatrix4fv(glGetUniformLocation(id, loc.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setVec4f(const std::string &loc, glm::vec4 val) const {
	glUniform4f(glGetUniformLocation(id, loc.c_str()), val.x, val.y, val.z, val.w);
}
