#include "App.hpp"
#include "helpers/Callbacks.hpp"
#include "objects/scenes/TriangleScene.hpp"
#include "objects/scenes/RectangleScene.hpp"
#include "objects/scenes/TexturedScene.hpp"
#include "objects/scenes/RotatingScene.hpp"
#include "objects/scenes/MaterialScene.hpp"
#include "objects/scenes/BezierScene.hpp"
#include "objects/scenes/EmptyScene.hpp"
#include "objects/scenes/SkyboxScene.hpp"
#include "objects/scenes/IndependantScene.hpp"

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

    // Init camera
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    camera->updateAspectRatio(800.0f, 600.0f);
    
    // Set up da callbacks
    Callbacks::init(camera.get(), this, 800.0f, 600.0f);
    glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Callbacks::mouse_callback);
    glfwSetScrollCallback(window, Callbacks::scroll_callback);
    glfwSetMouseButtonCallback(window, Callbacks::mouse_button_callback);
    glfwSetKeyCallback(window, Callbacks::key_callback);
    
    // Tell GLFW to capture mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // Set camera 4 controls
    Controls::setCamera(camera.get());

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!\n";
        return false;
    }

    // Enable depth testing for skybox
    glEnable(GL_DEPTH_TEST);

    scenes.emplace_back(std::make_unique<TriangleScene>());
    scenes.emplace_back(std::make_unique<RectangleScene>());
    scenes.emplace_back(std::make_unique<TexturedScene>());
    scenes.emplace_back(std::make_unique<RotatingScene>());
    scenes.emplace_back(std::make_unique<MaterialScene>());
    scenes.emplace_back(std::make_unique<BezierScene>());
    scenes.emplace_back(std::make_unique<EmptyScene>());
    scenes.emplace_back(std::make_unique<SkyboxScene>());
    scenes.emplace_back(std::make_unique<IndependantScene>());

    for (auto& scene : scenes) { // Camera everywhere now
        scene->setCamera(camera.get());
        scene->setWindow(window);
    }

    scenes[currentSceneIndex]->init();

    return true;
}

void App::run() {
    while (!glfwWindowShouldClose(window)) {
        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        Controls::processInput(window, deltaTime);

        int tabState = glfwGetKey(window, GLFW_KEY_TAB); // "Debounced"
        if (tabState == GLFW_PRESS && lastTabState == GLFW_RELEASE) {
            switchScene();
        }
        lastTabState = tabState;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    scenes[currentSceneIndex]->setCamera(camera.get()); // New scene gets a camera ref
    scenes[currentSceneIndex]->init();
}