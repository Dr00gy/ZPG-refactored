#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube texture_unit_id;

void main()
{    
    FragColor = texture(texture_unit_id, TexCoords);
}
