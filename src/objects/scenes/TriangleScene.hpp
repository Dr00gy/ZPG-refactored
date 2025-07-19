#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../objects/Model.hpp"
#include <memory>

class TriangleScene : public Scene {
private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;

public:
    void init() override;
    void render() override;
    void cleanup() override;
};