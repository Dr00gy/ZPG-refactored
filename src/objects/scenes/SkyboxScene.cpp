#include "SkyboxScene.hpp"
#include "../Camera.hpp"
#include "../Model.hpp"
#include <iostream>

SkyboxScene::SkyboxScene() 
    : cubemapFaces({
        "textures/skybox/right.png",   // +X (right)
        "textures/skybox/left.png",    // -X (left)  
        "textures/skybox/top.png",     // +Y (top)
        "textures/skybox/bottom.png",  // -Y (bottom)
        "textures/skybox/front.png",   // +Z (front)
        "textures/skybox/back.png"     // -Z (back)
      }) {}

SkyboxScene::SkyboxScene(const std::vector<std::string>& skyboxFaces) 
    : cubemapFaces(skyboxFaces) {}

SkyboxScene::~SkyboxScene() {
    cleanup();
}

void SkyboxScene::init() {
    skyboxShader = std::make_unique<Shader>(
        "shaders/skyboxVert.glsl",
        "shaders/skyboxFrag.glsl",
        true
    );

    if (skyboxShader->ID == 0) {
        std::cerr << "ERROR: Failed to compile skybox shaders!\n";
        return;
    }

    std::cout << "Loading skybox textures:\n";
    for (const auto& path : cubemapFaces) {
        std::cout << "  " << path << "\n";
    }
    
    skyboxTexture = std::make_shared<SkyboxTexture>(cubemapFaces);
    if (!skyboxTexture->isValid()) {
        std::cerr << "ERROR: Failed to load skybox cubemap textures!\n";
        return;
    }

    skyboxMaterial = std::make_shared<SkyboxMaterial>(skyboxTexture);
    createSkyboxCube();
    skyboxModel->setupAllMeshes();

    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture->getID());
    GLint width, height;
    glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_HEIGHT, &height);
    std::cout << "Skybox texture dimensions: " << width << "x" << height << std::endl;
}

void SkyboxScene::createSkyboxCube() {
    skyboxModel = Model::createCube(MeshType::UV);
}

void SkyboxScene::update(float deltaTime) {

}

void SkyboxScene::render() {
    if (!camera) return;
    
    glDepthFunc(GL_LEQUAL);
    
    skyboxShader->use();
    
    // Removing translation from the view matrix for skybox for infinite static skybox
    glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    glm::mat4 projection = camera->getProjectionMatrix();
    
    skyboxShader->setMat4("view", view);
    skyboxShader->setMat4("projection", projection);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture->getID());
    skyboxShader->setInt("skybox", 0);
    skyboxModel->draw();

    //skyboxMaterial->bind(*skyboxShader);
    //skyboxModel->draw();

    glDepthFunc(GL_LESS);
    
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << "\n";
    }
}

void SkyboxScene::cleanup() {
    if (skyboxModel) {
        skyboxModel->cleanup();
        skyboxModel.reset();
    }
    if (skyboxMaterial) {
        skyboxMaterial->cleanup();
    }
    if (skyboxTexture) {
        skyboxTexture->cleanup();
    }
    if (skyboxShader) {
        skyboxShader->deleteProgram();
    }
}