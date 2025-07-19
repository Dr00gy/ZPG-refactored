#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../shaders/Texture.hpp"
#include <memory>

class TexturedScene : public Scene {
public:
    TexturedScene();
    ~TexturedScene();

    void init() override;
    void render() override;
    void cleanup() override;

private:
    unsigned int VAO, VBO, EBO;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture;
};