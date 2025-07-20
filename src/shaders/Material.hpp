#pragma once
#include "Texture.hpp"
#include <optional>
#include <memory>

class Shader;

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    float specular = 0.75f;
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA
    
    virtual void bind(Shader& shader) const = 0;
    virtual void cleanup() {}
};