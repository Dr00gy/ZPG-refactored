#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() { // prolly simplest camera implementation
    // Transforms position to world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Transforms normal to world space (use normal matrix?)
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Just passing texCoords to frag
    TexCoord = aTexCoord;
    
    // Finally
    gl_Position = projection * view * vec4(FragPos, 1.0);
}