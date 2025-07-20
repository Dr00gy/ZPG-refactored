#version 450
layout(location = 0) in vec3 vp;

uniform mat4 view_mat;
uniform mat4 projection_mat;

out vec3 frag_pos;

void main()
{
    mat4 view_no_translation = mat4(mat3(view_mat));

    gl_Position = projection_mat * view_no_translation * vec4(vp, 1.0);
    frag_pos = vp;
}
