#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class Sphere : public Model {
public:
    Sphere(MeshType type = MeshType::NORMAL);
    Sphere(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<Sphere> create(MeshType type = MeshType::NORMAL);
    static std::shared_ptr<Sphere> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);

private:
    void setupDefaultShaderAndMaterial();
};