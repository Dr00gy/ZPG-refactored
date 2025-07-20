#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../shaders/SkyboxTexture.hpp"
#include "../../objects/Model.hpp"
#include <memory>
#include <vector>

class SkyboxScene : public Scene {
public:
    SkyboxScene();
    ~SkyboxScene();
    
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void cleanup() override;

    void handleKeyPress(int key) override; 

private:
    std::shared_ptr<Model> skyboxModel;
    std::unique_ptr<Shader> skyboxShader;
    std::unique_ptr<SkyboxTexture> skyboxTexture;
    std::vector<std::string> skyboxFaces;
    bool isInsideSkybox = true; 
};