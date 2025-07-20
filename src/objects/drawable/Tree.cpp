#include "Tree.hpp"
#include "../../../models/tree.h"

Tree::Tree(MeshType type) : Model() {
    size_t vertexCount = (sizeof(tree) / sizeof(float)) / 6;
    auto mesh = std::make_shared<Mesh>(tree, vertexCount, type);
    addMesh(mesh);
}

std::shared_ptr<Tree> Tree::create(MeshType type) {
    return std::make_shared<Tree>(type);
}