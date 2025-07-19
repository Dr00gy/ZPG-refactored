#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
    void deleteProgram();
};