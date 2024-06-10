#include "Shader.hpp"
#include "logger.hpp"

Shader::Shader(const std::string &vsh, const std::string &fsh) : id(glCreateProgram()) {
    unsigned int vertex, fragment;
    int status;
    char infoLog[512];

    std::string vCode_str, fCode_str;
    loadShaderSource(vsh, vCode_str, &status);
    if (!status) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::string error = infoLog;
        Logger::log(Logger::ERROR, "Shader", "Failed to load vertex shader due to error: " + error);
    }
    loadShaderSource(fsh, fCode_str, &status);
    if (!status) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::string error = infoLog;
        Logger::log(Logger::ERROR, "Shader", "Failed to load fragment shader due to error: " + error);
    }

    const char* vCode = vCode_str.c_str();
    const char* fCode = fCode_str.c_str();

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
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::string error = infoLog;
        Logger::log(Logger::ERROR, "Shader", "Failed to compile fragment shader due to error: " + error);
    }

    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetShaderiv(id, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
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
void Shader::loadShaderSource(const std::string &filename, std::string &out, int *status) const {
    *status = 0;
    std::ifstream file;
    file.open(filename.c_str());
    if (!file) {
        *status = 1;
        return;
    }
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    out = stream.str();
}
