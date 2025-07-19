#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../objects/Model.hpp"
#include "../../shaders/SkyboxTexture.hpp"
#include "../../shaders/SkyboxMaterial.hpp"
#include <memory>
#include <vector>
#include <string>

class SkyboxScene : public Scene {
public:
    SkyboxScene();
    SkyboxScene(const std::vector<std::string>& skyboxFaces); // Maybe for night
    ~SkyboxScene();
    
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void cleanup() override;

private:
    std::shared_ptr<Model> skyboxModel;
    std::unique_ptr<Shader> skyboxShader;
    std::shared_ptr<SkyboxTexture> skyboxTexture;
    std::shared_ptr<SkyboxMaterial> skyboxMaterial;
    
    std::vector<std::string> cubemapFaces;
    
    void createSkyboxCube();
};