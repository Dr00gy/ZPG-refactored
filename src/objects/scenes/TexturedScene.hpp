#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../shaders/Texture.hpp"
#include "../../objects/Model.hpp"
#include <memory>

class TexturedScene : public Scene {
public:
    TexturedScene();
    ~TexturedScene();
    
    void init() override;
    void render() override;
    void cleanup() override;

private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture;
};