#include "TriangleScene.hpp"

float triangleVertices[] = {
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

const char* vertexShaderSrc1 = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
})";

const char* fragmentShaderSrc1 = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(ourColor, 1.0);
})";

void TriangleScene::init() {
    shader = std::make_unique<Shader>(vertexShaderSrc1, fragmentShaderSrc1);
    mesh = std::make_unique<Mesh>(triangleVertices, sizeof(triangleVertices));
}

void TriangleScene::render() {
    shader->use();
    mesh->draw();
}

void TriangleScene::cleanup() {
    mesh->cleanup();
    shader->deleteProgram();
}
