#include "TriangleScene.hpp"
#include <memory>

void TriangleScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/vert.vert",
        "shaders/frag.frag",
        true
    );
    
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
        shader.reset();
    }
}