#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera; // Forward declaration
class App;

class Callbacks {
public:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static bool firstMouse;
    static float lastX;
    static float lastY;
    
    static Camera* currentCamera;
    static App* appInstance;
    
    // Init callback system
    static void init(Camera* camera, App* app = nullptr, float screenWidth = 800.0f, float screenHeight = 600.0f);
};