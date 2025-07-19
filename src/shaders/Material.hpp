#pragma once
#define MATERIAL_H

#include "Texture.hpp"
#include <optional>

class Material {
private:

public:
    Material() = default;
    ~Material() = default;

    float specular = 0.75f;
    float color[4] = { 1, 1, 1, 1 }; //white
    std::optional<Texture> texture = std::nullopt; // has_value() check
};
