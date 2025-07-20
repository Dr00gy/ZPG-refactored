#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class Creature : public Model {
public:
    static constexpr const char* CREATURE_MODEL_PATH = "../../../models/creature.obj";
    
    Creature(MeshType type = MeshType::UV);
    Creature(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<Creature> create(MeshType type = MeshType::UV);
    static std::shared_ptr<Creature> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
private:
    void setupDefaultShaderAndMaterial();
};