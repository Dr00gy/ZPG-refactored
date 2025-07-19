#include "Shader.hpp"
#include "../helpers/ShaderLoader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSrc, nullptr);
    glCompileShader(vertex);

    GLint success;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(vertex, 512, nullptr, log);
        std::cerr << "Vertex shader compilation failed:\n" << log << std::endl;
    }

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSrc, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(fragment, 512, nullptr, log);
        std::cerr << "Fragment shader compilation failed:\n" << log << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, bool fromFiles) {
    ShaderLoader loader;
    ID = loader.loadShader(vertexPath, fragmentPath);
    if (ID == 0) {
        std::cerr << "ERROR: Failed to compile/link skybox shaders!\n";
        std::cerr << "Vertex: " << vertexPath << "\n";
        std::cerr << "Fragment: " << fragmentPath << "\n";
    }
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::deleteProgram() {
    glDeleteProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}