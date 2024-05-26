#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform float u_time;
uniform sampler2D vehicle_texture;

void main()
{
    // frag_color = texture(vehicle_texture, tex_coord);
    frag_color = vec4(tex_coord[0], tex_coord[1], 0., 1.);
    // FragColor = vec4(0.50+sin(u_time*2)/2.0f, 0.50+sin(u_time*2+2.094f)/2.0f, 0.50+sin(u_time*2+4.189)/2.0f, 1.);
    // frag_color = vec4(1.0, 0.0, 0.0, 1.);
}