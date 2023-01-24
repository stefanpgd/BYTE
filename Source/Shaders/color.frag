#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D texture_albedo;

void main()
{
	vec3 diffuseTex = texture(texture_albedo, UV).rgb;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(FragPos);
	float diffuseFactor = max(dot(normal, -lightDir), 0.0);

	vec3 ambient = diffuseTex * 0.05;
	vec3 diffuse = diffuseTex * (diffuseFactor * 0.95);
	vec3 result = ambient + diffuse;

    FragColor = vec4(result, 1.0);
	BrightColor = vec4(result * 0.2, 1.0);
}