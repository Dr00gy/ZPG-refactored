#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

struct Material {
    vec4 color;
    float specular;
    sampler2D texture_diffuse;
};

uniform Material material;
uniform bool useTexture;

void main() {
    if (useTexture) {
        FragColor = texture(material.texture_diffuse, TexCoord) * material.color;
    } else {
        FragColor = material.color;
    }
}