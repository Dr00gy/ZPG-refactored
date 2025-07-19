#pragma once
#include "Material.hpp"

class ColorMaterial : public Material {
public:
    ColorMaterial(float R, float G, float B, float A = 1.0f) {
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = A;
    }

    void bind(Shader& shader) const {
        shader.setVec4("material.color", glm::vec4(color[0], color[1], color[2], color[3]));
        shader.setFloat("material.specular", specular);
        shader.setBool("useTexture", false);
    }
};