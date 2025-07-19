#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath, bool fromFiles);
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
    void deleteProgram();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};