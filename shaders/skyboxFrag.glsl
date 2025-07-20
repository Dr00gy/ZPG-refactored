#version 450

in vec3 frag_pos;

uniform samplerCube texture_unit_id;

out vec4 frag_colour;

void main()
{
    frag_colour = texture(texture_unit_id, frag_pos);
}
