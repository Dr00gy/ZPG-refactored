#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../objects/Model.hpp"
#include "../../shaders/ColorMaterial.hpp"
#include "../../shaders/TextureMaterial.hpp"
#include <memory>

class MaterialScene : public Scene {
private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;
    //std::shared_ptr<ColorMaterial> material;
    std::shared_ptr<TextureMaterial> material;

public:
    void init() override;
    void render() override;
    void cleanup() override;
};