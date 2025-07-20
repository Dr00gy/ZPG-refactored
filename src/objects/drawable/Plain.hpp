#pragma once
#include "../Model.hpp"

class Plain : public Model {
public:
    Plain(MeshType type = MeshType::UV);
    
    static std::shared_ptr<Plain> create(MeshType type = MeshType::UV);
};