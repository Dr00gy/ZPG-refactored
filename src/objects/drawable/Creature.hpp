#pragma once
#include "../Model.hpp"

class Creature : public Model {
public:
    static constexpr const char* CREATURE_MODEL_PATH = "../../../models/creature.obj";
    
    Creature(MeshType type = MeshType::UV);
    
    // Factory method for convenience
    static std::shared_ptr<Creature> create(MeshType type = MeshType::UV);
};