#include "TexturedScene.hpp"
#include <iostream>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aTexCoord;
    
    out vec2 texCoord;
    
    uniform mat4 model;
    
    void main()
    {
        gl_Position = model * vec4(aPos, 1.0);  // For model transformation
        texCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, texCoord);
}
)";

TexturedScene::TexturedScene() {}

TexturedScene::~TexturedScene() {
    cleanup();
}

void TexturedScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
    texture = std::make_unique<Texture>("textures/grass.png");
    
    // Square model with UV coordinates
    model = Model::createSquare(MeshType::UV);
    model->setupAllMeshes();

    model->setPosition(0.5f, 0.2f, 0.0f);        // Move right and up
    model->setRotation(0.0f, 0.0f, 0.785f);      // Rotate 45 degrees (π/4 radians) around Z
    model->setScale(1.5f, 1.0f, 1.0f);           // Scale wider on X axis
}

void TexturedScene::render() {
    shader->use();
    glm::mat4 modelMatrix = model->getModelMatrix();
    shader->setMat4("model", modelMatrix);
    texture->bind();
    model->draw();
}

void TexturedScene::cleanup() {
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