#include "RotatingScene.hpp"
#include "../Camera.hpp"
#include <iostream>

RotatingScene::RotatingScene() 
    : rotationAngle(0.0f) {}

RotatingScene::~RotatingScene() {
    cleanup();
}

void RotatingScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/cameraVert.glsl",
        "shaders/transFrag.glsl",
        true
    );
    texture = std::make_unique<Texture>("textures/grass.png");
    
    model = Model::createSquare(MeshType::UV);
    model->setupAllMeshes();
}

void RotatingScene::update(float deltaTime) {
    // Rotates 45 degrees around Z axis
    float rotationSpeed = glm::radians(45.0f);
    rotationAngle += rotationSpeed * deltaTime;

    rotationAngle = fmod(rotationAngle, glm::two_pi<float>()); // Keeps angle within 0-2π range to prevent overflow
    
    // Apply rotation
    model->setRotation(0.0f, 0.0f, rotationAngle);
}

void RotatingScene::render() {
    if (!camera) return;
    shader->use();
    glm::mat4 modelMatrix = model->getModelMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    shader->setMat4("model", modelMatrix);
    shader->setMat4("view", viewMatrix);
    shader->setMat4("projection", projectionMatrix);
    texture->bind();
    model->draw();
}

void RotatingScene::cleanup() {
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