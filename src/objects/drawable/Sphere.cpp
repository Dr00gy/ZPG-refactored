#include "Sphere.hpp"
#include "../../../models/sphere.h"

Sphere::Sphere(MeshType type) : Model() {
    size_t vertexCount = (sizeof(sphere) / sizeof(float)) / 6;
    auto mesh = std::make_shared<Mesh>(sphere, vertexCount, type);
    addMesh(mesh);
}

std::shared_ptr<Sphere> Sphere::create(MeshType type) {
    return std::make_shared<Sphere>(type);
}