#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../objects/Model.hpp"
#include <memory>

class IndependantScene : public Scene {
private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;

public:
    void init() override;
    virtual void update(float deltaTime) {}
    void render() override;
    void cleanup() override;
};