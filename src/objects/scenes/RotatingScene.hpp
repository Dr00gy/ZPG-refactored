#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../shaders/Texture.hpp"
#include "../../objects/Model.hpp"
#include <memory>

class RotatingScene : public Scene {
public:
    RotatingScene();
    ~RotatingScene();
    
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void cleanup() override;

private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture;
    float rotationAngle;
};