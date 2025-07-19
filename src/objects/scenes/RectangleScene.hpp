#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include <GL/glew.h>
#include <memory>

class RectangleScene : public Scene { // Decided to make seperated header and cpp files for each scene for potential modifs
private:
    GLuint VAO, VBO, EBO;
    std::unique_ptr<Shader> shader;

public:
    void init() override;
    void render() override;
    void cleanup() override;
};
