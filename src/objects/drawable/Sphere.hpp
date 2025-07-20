#pragma once
#include "../Model.hpp"

class Sphere : public Model {
public:
    Sphere(MeshType type = MeshType::NORMAL);
    
    static std::shared_ptr<Sphere> create(MeshType type = MeshType::NORMAL);
};