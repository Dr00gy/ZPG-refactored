#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../../objects/Model.hpp"
#include <vector>
#include <memory>

class EmptyScene : public Scene {
public:
    EmptyScene();
    ~EmptyScene();
    
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void cleanup() override;

    void handleMouseClick(int button, int action) override;

private:
    std::unique_ptr<Shader> shader;
    std::vector<std::shared_ptr<Model>> triangles;
    void createTriangle(glm::vec2 screenPos);
    void deleteTriangleAt(glm::vec2 screenPos);
};