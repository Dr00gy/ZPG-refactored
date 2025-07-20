#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class House : public Model {
public:
    static constexpr const char* HOUSE_MODEL_PATH = "../../../models/model.obj";
    
    House(MeshType type = MeshType::UV);
    House(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<House> create(MeshType type = MeshType::UV);
    static std::shared_ptr<House> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);

private:
    void setupDefaultShaderAndMaterial();
};