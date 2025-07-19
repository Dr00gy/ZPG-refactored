#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>

class SkyboxTexture {
public:
    SkyboxTexture(const std::vector<std::string>& faces);
    ~SkyboxTexture();

    void bind() const;
    void cleanup();
    bool isValid() const;
    GLuint getID() const { return ID; }
private:
    GLuint ID;
    bool loadCubemap(const std::vector<std::string>& faces);
};