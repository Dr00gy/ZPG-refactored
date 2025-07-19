#include "App.hpp"
#include "helpers/Callbacks.hpp"
#include "objects/scenes/TriangleScene.hpp"
#include "objects/scenes/RectangleScene.hpp"
#include "objects/scenes/TexturedScene.hpp"
#include "objects/scenes/RotatingScene.hpp"
#include "objects/scenes/MaterialScene.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


App::App() : window(nullptr), currentSceneIndex(0), lastTabState(GLFW_RELEASE) {}

App::~App() {
    cleanup();
}

bool App::init() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG OpenGL Projekt", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!\n";
        return false;
    }

    scenes.emplace_back(std::make_unique<TriangleScene>());
    scenes.emplace_back(std::make_unique<RectangleScene>());
    scenes.emplace_back(std::make_unique<TexturedScene>());
    scenes.emplace_back(std::make_unique<RotatingScene>());
    scenes.emplace_back(std::make_unique<MaterialScene>());
    scenes[currentSceneIndex]->init();

    return true;
}

void App::run() {
    while (!glfwWindowShouldClose(window)) {
        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        Controls::processInput(window);

        int tabState = glfwGetKey(window, GLFW_KEY_TAB); // "Debounced"
        if (tabState == GLFW_PRESS && lastTabState == GLFW_RELEASE) {
            switchScene();
        }
        lastTabState = tabState;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scenes[currentSceneIndex]->update(deltaTime);
        scenes[currentSceneIndex]->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::cleanup() {
    if (mesh) mesh->cleanup();
    if (shader) shader->deleteProgram();

    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}

void App::switchScene() {
    scenes[currentSceneIndex]->cleanup();
    currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
    scenes[currentSceneIndex]->init();
}