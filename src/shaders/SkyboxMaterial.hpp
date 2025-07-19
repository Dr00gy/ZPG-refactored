#pragma once
#include "Material.hpp"
#include "SkyboxTexture.hpp"
#include <memory>

class SkyboxMaterial : public Material {
private:
    std::shared_ptr<SkyboxTexture> skyboxTexture;

public:
    SkyboxMaterial(std::shared_ptr<SkyboxTexture> texture) : skyboxTexture(texture) {}

    void bind(Shader& shader) const override {
        if (skyboxTexture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture->getID());
            shader.setInt("skybox", 0);
        }
    }

    void cleanup() override {
        if (skyboxTexture) {
            skyboxTexture->cleanup();
        }
    }
};