#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../shaders/Texture.hpp"
#include "../../objects/Model.hpp"
#include "../BezierCurve.hpp"
#include <memory>
#include <glm/glm.hpp>

class BezierScene : public Scene {
public:
    BezierScene();
    ~BezierScene();
    
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void cleanup() override;

private:
    std::shared_ptr<Model> model;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture;
    
    BezierCurve bezierCurve;
    glm::mat4x3 controlPoints;
    float t; // bezier param (0.0 to 1.0)
    float speed; // sspeed
    bool reverse; // direction
    
    void setupControlPoints();
};