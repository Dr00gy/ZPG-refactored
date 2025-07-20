#version 450

in vec3 frag_pos;

uniform samplerCube texture_unit_id;

out vec4 frag_colour;

void main()
{
    //frag_colour = texture(texture_unit_id, frag_pos);
    frag_colour = vec4(0.0f, 0.5f, 1.0f, 1.0f);
}
