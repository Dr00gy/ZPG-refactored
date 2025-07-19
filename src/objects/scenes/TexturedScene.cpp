#include "TexturedScene.hpp"
#include <iostream>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
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
}

void TexturedScene::render() {
    shader->use();
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