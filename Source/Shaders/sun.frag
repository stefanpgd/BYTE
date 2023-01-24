#version 460 core
in vec3 Normal;
in vec2 UV;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float intensity;
uniform float time;

uniform sampler2D texture_albedo;

void main()
{
    vec2 uvCoords = UV;
	uvCoords.x += time * 0.15;

	vec3 col = color * (intensity * texture(texture_albedo, uvCoords).r);
	FragColor = vec4(col, 1.0);
	BrightColor = vec4(col, 1.0);
}