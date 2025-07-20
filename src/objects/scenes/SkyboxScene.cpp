#include "SkyboxScene.hpp"
#include "../Camera.hpp"
#include "../drawable/Cube.hpp"
#include <iostream>

SkyboxScene::SkyboxScene() {
    skyboxFaces = {
        "textures/skybox/right.png",
        "textures/skybox/left.png",
        "textures/skybox/top.png",
        "textures/skybox/bottom.png",
        "textures/skybox/front.png",
        "textures/skybox/back.png"
    };
}

SkyboxScene::~SkyboxScene() {
    cleanup();
}

void SkyboxScene::init() {
    skyboxShader = std::make_unique<Shader>(
        "shaders/skyboxVert.glsl",
        "shaders/skyboxFrag.glsl",
        true
    );
    
    skyboxTexture = std::make_unique<SkyboxTexture>(skyboxFaces);
    skyboxModel = Cube::create(MeshType::BASIC);
    skyboxModel->setScale(50.0f); // Make it large enough to contain the scene
    skyboxModel->setupAllMeshes();

    isInsideSkybox = true;
}

void SkyboxScene::handleKeyPress(int key) {
    if (key == GLFW_KEY_Q) {
        isInsideSkybox = !isInsideSkybox;
    }
}

void SkyboxScene::update(float deltaTime) {
    // rotation?
}

void SkyboxScene::render() {
    if (!camera) return;
    
    // Draw skybox behind everything else
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    skyboxShader->use();
    skyboxShader->setBool("isInside", isInsideSkybox);
    
    glm::mat4 view;
    if (isInsideSkybox) {
        // Static
        view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    } else {
        // Regular view from outside
        view = camera->getViewMatrix();
    }
    
    glm::mat4 projection = camera->getProjectionMatrix();
    skyboxShader->setMat4("view", view);
    skyboxShader->setMat4("projection", projection);

    glDisable(GL_CULL_FACE);
    
    skyboxTexture->bind(GL_TEXTURE0);
    skyboxShader->setInt("texture_unit_id", 0);
    
    skyboxModel->draw();
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void SkyboxScene::cleanup() {
    if (skyboxModel) {
        skyboxModel->cleanup();
        skyboxModel.reset();
    }
    if (skyboxTexture) {
        skyboxTexture->cleanup();
    }
    if (skyboxShader) {
        skyboxShader->deleteProgram();
    }
}