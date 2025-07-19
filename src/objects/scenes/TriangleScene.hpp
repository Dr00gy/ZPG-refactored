#pragma once
#include "../Scene.hpp"
#include "../../shaders/Shader.hpp"
#include "../Mesh.hpp"
#include <memory>

class TriangleScene : public Scene {
private:
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Shader> shader;

public:
    void init() override;
    void render() override;
    void cleanup() override;
};
