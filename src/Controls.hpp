#pragma once
#include <GLFW/glfw3.h>

class Controls {
    private:
    public:
    static void processInput(GLFWwindow *window);
    Controls(GLFWwindow* window);
    ~Controls() = default;
};