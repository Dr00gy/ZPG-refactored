#include "IndependantScene.hpp"
#include "../../shaders/ColorMaterial.hpp"
#include <iostream>

void IndependantScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/material.vert",
        "shaders/material.frag",
        true
    );
    
    model = Model::createTriangle(MeshType::BASIC);
    auto orangeMaterial = std::make_shared<ColorMaterial>(1.0f, 0.5f, 1.0f, 1.0f);
    
    model->setMaterial(orangeMaterial);
    model->setShader(std::shared_ptr<Shader>(shader.release()));
    
    model->setupAllMeshes();
}

void IndependantScene::render() {
    model->draw();
}

void IndependantScene::cleanup() {
    if (model) {
        model->cleanup();
        model.reset();
    }
    if (shader) {
        shader->deleteProgram();
    }
}