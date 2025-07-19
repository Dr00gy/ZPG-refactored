#include "TriangleScene.hpp"

const char* vertexShaderSrc1 = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
})";

const char* fragmentShaderSrc1 = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(ourColor, 1.0);
})";

void TriangleScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSrc1, fragmentShaderSrc1);
    
    // Per-vertex colors
    auto mesh = std::make_shared<Mesh>(MeshType::NORMAL); // NORMAL type to access color attribute
    
    // Creating a simple shape without the factory method
    // Vertices with positions and colors (using normal field for colors)
    mesh->addVertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));    // Top - Blue
    mesh->addVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // Bottom-left - Green
    mesh->addVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));   // Bottom-right - Red
    
    model = std::make_shared<Model>(mesh);
    model->setupAllMeshes();
}

void TriangleScene::render() {
    shader->use();
    model->draw();
}

void TriangleScene::cleanup() {
    if (model) {
        model->cleanup();
        model.reset();
    }
    if (shader) {
        shader->deleteProgram();
    }
}