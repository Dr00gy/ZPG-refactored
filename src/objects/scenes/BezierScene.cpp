#include "BezierScene.hpp"
#include "../Camera.hpp"
#include <iostream>

BezierScene::BezierScene() 
    : t(0.0f), speed(0.3f), reverse(false) {}

BezierScene::~BezierScene() {
    cleanup();
}

void BezierScene::init() {
    shader = std::make_unique<Shader>(
        "shaders/cameraVert.glsl",
        "shaders/transFrag.glsl",
        true
    );
    texture = std::make_unique<Texture>("textures/grass.png");
    
    model = Model::createTriangle(MeshType::UV);
    model->setupAllMeshes();
    
    setupControlPoints();
}

void BezierScene::setupControlPoints() {
    controlPoints = glm::mat4x3(
        glm::vec3(-2.0f, -1.0f, 0.0f),  // P0 - start point
        glm::vec3(-1.0f,  2.0f, 0.0f),  // P1 - first control point
        glm::vec3( 1.0f,  2.0f, 0.0f),  // P2 - second control point  
        glm::vec3( 2.0f, -1.0f, 0.0f)   // P3 - end point
    );
}

void BezierScene::update(float deltaTime) {
    // Parameter t updated along the curve
    if (reverse) {
        t -= speed * deltaTime;
        if (t <= 0.0f) {
            t = 0.0f;
            reverse = false;
        }
    } else {
        t += speed * deltaTime;
        if (t >= 1.0f) {
            t = 1.0f;
            reverse = true;
        }
    }
    
    // Gets position on Bezier curve and sets model
    glm::vec3 position = bezierCurve.evaluate(controlPoints, t);
    model->setPosition(position.x, position.y, position.z);
    
    // For visual purposes we calculate the tangent for rotation (makes triangle face direction of movement)
    if (t > 0.0f && t < 1.0f) {
        float deltaT = 0.01f;
        glm::vec3 nextPos = bezierCurve.evaluate(controlPoints, std::min(t + deltaT, 1.0f));
        glm::vec3 prevPos = bezierCurve.evaluate(controlPoints, std::max(t - deltaT, 0.0f));
        
        glm::vec3 tangent = glm::normalize(nextPos - prevPos);
        float angle = atan2(tangent.y, tangent.x);
        
        model->setRotation(0.0f, 0.0f, angle);
    }
}

void BezierScene::render() {
    if (!camera) return;
    
    shader->use();
    glm::mat4 modelMatrix = model->getModelMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    
    shader->setMat4("model", modelMatrix);
    shader->setMat4("view", viewMatrix);
    shader->setMat4("projection", projectionMatrix);
    
    texture->bind();
    model->draw();
}

void BezierScene::cleanup() {
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