#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class Bush : public Model {
public:
    Bush(MeshType type = MeshType::NORMAL);
    Bush(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<Bush> create(MeshType type = MeshType::NORMAL);
    static std::shared_ptr<Bush> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);

private:
    void setupDefaultShaderAndMaterial();
};