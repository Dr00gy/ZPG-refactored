#include "SkyboxTexture.hpp"
#include <iostream>
#include "/usr/include/stb/stb_image.h"

SkyboxTexture::SkyboxTexture(const std::vector<std::string>& faces) {
    if (!loadCubemap(faces)) {
        std::cerr << "Failed to load skybox cubemap" << std::endl;
    }
}

SkyboxTexture::~SkyboxTexture() {
    cleanup();
}

bool SkyboxTexture::loadCubemap(const std::vector<std::string>& faces) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            std::cerr << "FAILED TO LOAD CUBEMAP FACE: " << faces[i] 
                      << " REASON: " << stbi_failure_reason() << std::endl;
            stbi_image_free(data);
            return false;
        }

        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        std::cout << "Loaded face " << i << ": " << faces[i] 
                  << " (" << width << "x" << height << ")" << std::endl;

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                     0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return true;
}

void SkyboxTexture::bind() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void SkyboxTexture::cleanup() {
    if (ID) {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}

bool SkyboxTexture::isValid() const {
    return ID != 0;
}