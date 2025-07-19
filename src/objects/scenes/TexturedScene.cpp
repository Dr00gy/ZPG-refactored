#include "TexturedScene.hpp"
#include <iostream>

TexturedScene::TexturedScene() {}

TexturedScene::~TexturedScene() {
    cleanup();
}

void TexturedScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/texVert.glsl",
        "shaders/texFrag.glsl",
        true
    );
    texture = std::make_unique<Texture>("textures/grass.png");
    
    // Square model with UV coordinates
    model = Model::createSquare(MeshType::UV);
    model->setupAllMeshes();

    model->setPosition(0.5f, 0.2f, 0.0f);        // Move right and up
    model->setRotation(0.0f, 0.0f, 0.785f);      // Rotate 45 degrees (π/4 radians) around Z
    model->setScale(1.5f, 1.0f, 1.0f);           // Scale wider on X axis
}

void TexturedScene::render() {
    shader->use();
    glm::mat4 modelMatrix = model->getModelMatrix();
    shader->setMat4("model", modelMatrix);
    texture->bind();
    model->draw();
}

void TexturedScene::cleanup() {
    if (model) {
        model->cleanup();
        model.reset();
    }
    if (texture) {
        texture->cleanup();
    }
    if (shader) {
        shader->deleteProgram();
    }
}