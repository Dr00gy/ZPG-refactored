#include "RectangleScene.hpp"
#include <iostream>

const char* vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
})";

const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.9, 0.4, 0.3, 1.0); // fixed orange color
})";

void RectangleScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSrc, fragmentShaderSrc);
    
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