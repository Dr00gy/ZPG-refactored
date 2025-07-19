#include "Callbacks.hpp"
#include "../objects/Camera.hpp"
#include "../App.hpp"

bool Callbacks::firstMouse = true;
float Callbacks::lastX = 400.0f;
float Callbacks::lastY = 300.0f;
Camera* Callbacks::currentCamera = nullptr;
App* Callbacks::appInstance = nullptr;

void Callbacks::init(Camera* camera, App* app, float screenWidth, float screenHeight) {
    currentCamera = camera;
    appInstance = app;
    lastX = screenWidth / 2.0f;
    lastY = screenHeight / 2.0f;
    firstMouse = true;
}

void Callbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    
    // Update camera aspect ratio when resizing win
    if (currentCamera) {
        currentCamera->updateAspectRatio(static_cast<float>(width), static_cast<float>(height));
    }
}

void Callbacks::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!currentCamera) return;
    
    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // Reversed bcs y-coordinates go from bottom to top
    
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    currentCamera->processMouseMovement(xoffset, yoffset);
}

void Callbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action != GLFW_PRESS) return;
    
    // Forward 2 the current scene if we have a current scene in App
    if (appInstance && appInstance->getCurrentScene()) {
        appInstance->getCurrentScene()->handleMouseClick(button, action);
    }
}


void Callbacks::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (!currentCamera) return;
    
    currentCamera->processMouseScroll(static_cast<float>(yoffset));
}