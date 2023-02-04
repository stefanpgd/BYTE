#version 460 core
in vec2 UV;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D texture_albedo;
uniform int framesInTexture;
uniform int currentFrame;

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

    FragColor = vec4(diffuseTex.rgb, 1.0);
	BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}