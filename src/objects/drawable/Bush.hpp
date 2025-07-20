#pragma once
#include "../Model.hpp"

class Bush : public Model {
public:
    Bush(MeshType type = MeshType::NORMAL);
    
    static std::shared_ptr<Bush> create(MeshType type = MeshType::NORMAL);
};