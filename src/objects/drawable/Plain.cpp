#include "Plain.hpp"
#include "../../../models/plain.h"

Plain::Plain(MeshType type) : Model() {
    size_t vertexCount = (sizeof(plain) / sizeof(float)) / 8;
    auto mesh = std::make_shared<Mesh>(plain, vertexCount, type);
    addMesh(mesh);
}

std::shared_ptr<Plain> Plain::create(MeshType type) {
    return std::make_shared<Plain>(type);
}