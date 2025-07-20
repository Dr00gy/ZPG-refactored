#pragma once
#include "../Model.hpp"

class Cube : public Model {
public:
    Cube(MeshType type = MeshType::BASIC);
    
    static std::shared_ptr<Cube> create(MeshType type = MeshType::BASIC);
};