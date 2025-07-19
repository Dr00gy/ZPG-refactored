#include "Controls.hpp"
#include "objects/Camera.hpp"
#include <GLFW/glfw3.h>

Camera* Controls::currentCamera = nullptr;

void Controls::setCamera(Camera* camera) {
    currentCamera = camera;
}

void Controls::processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (currentCamera) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            currentCamera->processKeyboard(CameraMovement::DOWN, deltaTime);
    }
}

void Controls::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Controls::Controls(GLFWwindow* window) {
    // Might use this later
}