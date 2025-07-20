#include "Cube.hpp"
#include "../../../models/cube.h"

Cube::Cube(MeshType type) : Model() {
    size_t vertexCount = (sizeof(cube) / sizeof(float)) / 3;
    auto mesh = std::make_shared<Mesh>(cube, vertexCount, type);
    addMesh(mesh);
}

std::shared_ptr<Cube> Cube::create(MeshType type) {
    return std::make_shared<Cube>(type);
}