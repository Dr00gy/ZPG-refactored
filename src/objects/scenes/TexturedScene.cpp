#include "TexturedScene.hpp"
#include <GL/glew.h>
#include <memory>

float vertices3[] = {
    // pos         // color          // tex
     0.5f,  0.5f, 0.0f,  1.f, 0.f, 0.f,  1.f, 1.f, // top right
     0.5f, -0.5f, 0.0f,  0.f, 1.f, 0.f,  1.f, 0.f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.f, 0.f, 1.f,  0.f, 0.f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.f, 1.f, 0.f,  0.f, 1.f  // top left
};

unsigned int indices3[] = {
    0, 1, 3,
    1, 2, 3
};

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 texCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    texCoord = aTexCoord;
})";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0);
})";

TexturedScene::TexturedScene() : VAO(0), VBO(0), EBO(0) {}

TexturedScene::~TexturedScene() {
    cleanup();
}

void TexturedScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
    texture = std::make_unique<Texture>("textures/grass.png");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // TexCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void TexturedScene::render() {
    shader->use();
    texture->bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TexturedScene::cleanup() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
    if (texture) texture->cleanup();
    if (shader) shader->deleteProgram();
}
