#include "RotatingScene.hpp"
#include <iostream>

const char* vertexShaderSource4 = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aTexCoord;
    
    out vec2 texCoord;
    
    uniform mat4 model;
    
    void main()
    {
        gl_Position = model * vec4(aPos, 1.0);
        texCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource4 = R"(
    #version 330 core
    in vec2 texCoord;
    out vec4 FragColor;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, texCoord);
    }
)";

RotatingScene::RotatingScene() 
    : rotationAngle(0.0f) {}

RotatingScene::~RotatingScene() {
    cleanup();
}

void RotatingScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSource4, fragmentShaderSource4);
    texture = std::make_unique<Texture>("textures/grass.png");
    
    model = Model::createSquare(MeshType::UV);
    model->setupAllMeshes();
}

void RotatingScene::update(float deltaTime) {
    // Rotates 45 degrees around Z axis
    float rotationSpeed = glm::radians(45.0f);
    rotationAngle += rotationSpeed * deltaTime;

    rotationAngle = fmod(rotationAngle, glm::two_pi<float>()); // Keeps angle within 0-2π range to prevent overflow
    
    // Apply rotation
    model->setRotation(0.0f, 0.0f, rotationAngle);
}

void RotatingScene::render() {
    shader->use();
    glm::mat4 modelMatrix = model->getModelMatrix();
    shader->setMat4("model", modelMatrix);
    texture->bind();
    model->draw();
}

void RotatingScene::cleanup() {
    if (model) {
        model->cleanup();
        model.reset();
    }
    if (texture) {
        texture->cleanup();
    }
    if (shader) {
        shader->deleteProgram();
    }
}