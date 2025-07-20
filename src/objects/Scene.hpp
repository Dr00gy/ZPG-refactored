#define GLM_ENABLE_EXPERIMENTAL
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera; // Forward declaration

class Scene {
public:
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(float deltaTime) {}
    virtual void render() = 0;
    virtual void cleanup() = 0;
    virtual void setCamera(Camera* camera) { this->camera = camera; }
    virtual void handleMouseClick(int button, int action) {}
    void setWindow(GLFWwindow* win) { window = win; }
    virtual void handleKeyPress(int key) {}
protected:
    GLFWwindow* window = nullptr;
    Camera* camera = nullptr;
};