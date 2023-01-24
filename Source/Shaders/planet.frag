#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float time;
uniform vec3 starColor;

uniform sampler2D texture_albedo;

void main()
{
	vec3 textureColor = texture(texture_albedo, UV).rgb;
	vec3 c = color;

	if(textureColor != vec3(0.0, 0.0, 0.0))
	{
		c = textureColor;
	}

	float diff = dot(Normal, -FragPos);
	vec3 ambient = (c * 0.01);
	vec3 diffuse;

	float mag = length(FragPos);
	float linearFallof = 1.5;
	float attentuation = 1.0 / (1.0 + linearFallof * mag);

	if(diff > 0)
	{
		diffuse = (c * starColor) * diff;
	}

	vec3 col = ambient + (diffuse * attentuation);
	FragColor = vec4(col, 1.0);

	float brightness = dot(FragColor.rgb, vec3(0.8, 0.8, 0.8));
	if(brightness > 1.0)
	{
		BrightColor = vec4(col, 1.0) * 0.05;
	}
	else
	{
		BrightColor = vec4(0, 0, 0, 1.0);
	}
}