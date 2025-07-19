#pragma once
#include <GL/glew.h>

class Mesh {
public:
    GLuint VAO, VBO;

    Mesh(float* vertices, size_t vertSize);
    void draw();
    void cleanup();
};
