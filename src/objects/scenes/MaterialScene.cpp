#include "MaterialScene.hpp"
#include <iostream>

void MaterialScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/material.vert",
        "shaders/material.frag",
        true
    );

    if (shader->ID == 0) {
        std::cerr << "Shader failed to compile or load!" << std::endl;
        return;
    }
    
    // Examples here (comment/uncomment for color or texture test)
    //material = std::make_shared<ColorMaterial>(1.0f, 0.0f, 0.0f, 1.0f);
    auto texture = std::make_shared<Texture>("textures/grass.png");
    material = std::make_shared<TextureMaterial>(texture);
    
    //model = Model::createSquare(MeshType::BASIC);
    model = Model::createSquare(MeshType::UV);
    model->setupAllMeshes();
}

void MaterialScene::render() {
    shader->use();

    //glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = model->getModelMatrix();
    shader->setMat4("model", modelMatrix);

    shader->setBool("useTexture", false); // not using a texture atm
    material->bind(*shader);
    model->draw();
}

void MaterialScene::cleanup() {
    if (model) model->cleanup();
    if (shader) shader->deleteProgram();
    if (material) material->cleanup();
}