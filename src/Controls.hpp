#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera; // Forward declaration

class Controls {
private:
    static Camera* currentCamera;
    
public:
    static void setCamera(Camera* camera);
    static void processInput(GLFWwindow* window, float deltaTime);
    static void processInput(GLFWwindow* window); // Keeping old version for now
    
    Controls(GLFWwindow* window);
    ~Controls() = default;
};