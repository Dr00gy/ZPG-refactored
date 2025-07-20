#include "Bush.hpp"
#include "../../../models/bushes.h"

Bush::Bush(MeshType type) : Model() {
    size_t vertexCount = (sizeof(bushes) / sizeof(float)) / 6;
    auto mesh = std::make_shared<Mesh>(bushes, vertexCount, type);
    addMesh(mesh);
}

std::shared_ptr<Bush> Bush::create(MeshType type) {
    return std::make_shared<Bush>(type);
}