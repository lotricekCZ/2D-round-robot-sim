#version 330 core

uniform mat4 u_proj;

in vec4 v_data;

out vec2 tex_coord;

void main()
{
    gl_Position = u_proj * vec4(v_data.x, v_data.y, 0., 1.);
    tex_coord = vec2(v_data[2], v_data[3]);
}