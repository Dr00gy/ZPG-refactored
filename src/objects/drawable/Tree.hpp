#pragma once
#include "../Model.hpp"

class Tree : public Model {
public:
    Tree(MeshType type = MeshType::NORMAL);
    
    static std::shared_ptr<Tree> create(MeshType type = MeshType::NORMAL);
};