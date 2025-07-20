#include "EmptyScene.hpp"
#include "../Camera.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

EmptyScene::EmptyScene() {}

EmptyScene::~EmptyScene() {
    cleanup();
}

void EmptyScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/stencilVert.glsl",
        "shaders/basicFrag.glsl",
        true
    );
    
    // Enable stencil testing
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void EmptyScene::update(float deltaTime) {
    // No continuous updates needed
}

void EmptyScene::render() {
    if (!camera) return;
    
    // Clear stencil buffer along with color and depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    shader->use();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    for (size_t i = 0; i < triangles.size(); ++i) {
        glStencilFunc(GL_ALWAYS, i + 1, 0xFF); // 1 triangle == 1 unique ID (1-based)
        
        glm::mat4 modelMatrix = triangles[i]->getModelMatrix(); // Set model matrix so its not in the middle of the screen
        shader->setMat4("model", modelMatrix);
        
        triangles[i]->draw();
    }
}

void EmptyScene::cleanup() {
    triangles.clear();
    if (shader) {
        shader->deleteProgram();
    }
    glDisable(GL_STENCIL_TEST);
}

void EmptyScene::handleMouseClick(int button, int action) {
    if (action != GLFW_PRESS) return;
    
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        createTriangle(glm::vec2(x, y));
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        deleteTriangleAt(glm::vec2(x, y));
    }
}

void EmptyScene::createTriangle(glm::vec2 screenPos) { // Convert screen coords to world coords
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    float ndc_x = (screenPos.x / width) * 2.0f - 1.0f; // Normalising (screen to device)
    float ndc_y = 1.0f - (screenPos.y / height) * 2.0f;

    glm::vec4 clipSpacePos = glm::vec4(ndc_x, ndc_y, 0.8f, 1.0f); // Z of -1.0f is very close to camera (near plane)

    glm::mat4 invMVP = glm::inverse(camera->getProjectionMatrix() * camera->getViewMatrix());
    glm::vec4 worldSpacePos = invMVP * clipSpacePos; // World space now

    if (worldSpacePos.w != 0.0f) { // From homo
        worldSpacePos /= worldSpacePos.w;
    }
    
    auto triangle = Model::createTriangle(MeshType::BASIC);
    triangle->setPosition(worldSpacePos.x, worldSpacePos.y, worldSpacePos.z);
    triangle->setScale(0.2f);
    triangles.push_back(triangle);
}

void EmptyScene::deleteTriangleAt(glm::vec2 screenPos) {
    if (triangles.empty()) return;
    
    // Read the stencil value at click pos
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    GLint stencilValue = 0;
    glReadPixels(
        static_cast<int>(screenPos.x), 
        height - static_cast<int>(screenPos.y),  // Flips y-coordinate
        1, 1, 
        GL_STENCIL_INDEX, 
        GL_INT, 
        &stencilValue
    );
    
    // Checks if we clicked on a triangle (stencilValue is 1-based index)
    if (stencilValue > 0 && stencilValue <= static_cast<GLint>(triangles.size())) {
        triangles.erase(triangles.begin() + (stencilValue - 1));
    }
}