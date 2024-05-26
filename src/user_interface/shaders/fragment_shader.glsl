#version 330 core

out vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D vehicle_texture;
uniform sampler2D bot_texture;

void main()
{
    frag_color = texture(vehicle_texture, tex_coord);
}