#version 460 core
in vec2 UV;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D texture_albedo;
uniform int framesInTexture;
uniform int currentFrame;

uniform vec4 color;
uniform float emission;

void main()
{
	float frameSize = 1.0 / framesInTexture;
	float framePosition = frameSize * currentFrame;
	vec2 uv = vec2(UV.x / framesInTexture + framePosition, UV.y);
	vec4 diffuseTex = texture(texture_albedo, uv);

	if(diffuseTex.a < 0.5)
	{
		discard;
	}

	if(color != vec4(0.0, 0.0, 0.0, 0.0))
	{
		diffuseTex.rgb *= color.rgb;

		FragColor = vec4(diffuseTex.rgb, color.a);
		BrightColor = vec4(diffuseTex.rgb * emission, 1.0);
		return;
	}

    FragColor = vec4(diffuseTex.rgb, 1.0);
	BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}