#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include <iostream>
#include <memory>
#include <vector>

#include "shaders/Shader.hpp"
#include "objects/Mesh.hpp"
#include "Controls.hpp"
#include "objects/Scene.hpp"

class App {
private:
    GLFWwindow* window;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Mesh> mesh;
    std::vector<std::unique_ptr<Scene>> scenes;
    int currentSceneIndex = 0;

public:
    App();
    ~App();

    int lastTabState;

    bool init();
    void run();
    void cleanup();
    void switchScene();
};
