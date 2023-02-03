#version 460 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float emission;

void main()
{
    FragColor = vec4(color, 1.0);
	BrightColor = vec4(color * emission, 1.0);
}