#pragma once
#include "Material.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp> // Include glm headers

class TextureMaterial : public Material {
private:
    std::shared_ptr<Texture> texture;

public:
    TextureMaterial(std::shared_ptr<Texture> tex) : texture(tex) {}

    void bind(Shader& shader) const override {
        if (texture) {
            texture->bind(GL_TEXTURE0);
            shader.setInt("material.texture_diffuse", 0);
            shader.setBool("useTexture", true);
        }
        // vec4 directly from array elements
        shader.setVec4("material.color", glm::vec4(color[0], color[1], color[2], color[3]));
        shader.setFloat("material.specular", specular);
    }

    void cleanup() override {
        if (texture) {
            texture->cleanup();
        }
    }
};