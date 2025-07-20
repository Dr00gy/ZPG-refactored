#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>

class SkyboxTexture {
public:
    SkyboxTexture(const std::vector<std::string>& faces);
    ~SkyboxTexture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void cleanup();

private:
    GLuint ID;
};