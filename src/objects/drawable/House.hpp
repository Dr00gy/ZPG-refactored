#pragma once
#include "../Model.hpp"

class House : public Model {
public:
    static constexpr const char* HOUSE_MODEL_PATH = "../../../models/model.obj";
    
    House(MeshType type = MeshType::UV);
    
    // Factory methods for convenience
    static std::shared_ptr<House> create(MeshType type = MeshType::UV);
};