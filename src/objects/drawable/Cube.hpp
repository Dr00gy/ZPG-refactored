#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class Cube : public Model {
public:
    Cube(MeshType type = MeshType::BASIC);
    Cube(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<Cube> create(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Cube> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);

private:
    void setupDefaultShaderAndMaterial();
};