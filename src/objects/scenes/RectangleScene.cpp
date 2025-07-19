#include "RectangleScene.hpp"
#include <iostream>

void RectangleScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/vert2.vert",
        "shaders/frag2.frag",
        true
    );
    
    // Creating a simple shape WITH a factory method
    model = Model::createSquare(MeshType::BASIC);
    model->setupAllMeshes();
}

void RectangleScene::render() {
    shader->use();
    model->draw();
}

void RectangleScene::cleanup() {
    if (model) {
        model->cleanup();
        model.reset();
    }
    if (shader) {
        shader->deleteProgram();
    }
}