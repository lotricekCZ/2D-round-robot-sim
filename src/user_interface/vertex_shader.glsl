#version 330 core

uniform mat4 u_proj;

layout(location = 0) in vec2 vPos;
// layout(location = 1) in vec3 vColor;
layout(location = 1) in vec2 vTexCoord;

// out vec3 our_color;
out vec2 tex_coord;
// out float 

void main()
{
    gl_Position = u_proj * vec4(vPos, 0., 1.);
    // ourColor = vColor;
    tex_coord = vTexCoord;
}