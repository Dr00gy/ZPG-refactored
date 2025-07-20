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
}

void SkyboxScene::update(float deltaTime) {
    // rotation?
}

void SkyboxScene::render() {
    if (!camera) return;
    
    // Draw skybox first (with depth test disabled)
    glDepthMask(GL_FALSE);
    skyboxShader->use();
    
    glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    glm::mat4 projection = camera->getProjectionMatrix();
    
    skyboxShader->setMat4("view_mat", view);
    skyboxShader->setMat4("projection_mat", projection);
    
    skyboxTexture->bind(GL_TEXTURE0);
    skyboxShader->setInt("texture_unit_id", 0);
    
    skyboxModel->draw();
    glDepthMask(GL_TRUE);
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