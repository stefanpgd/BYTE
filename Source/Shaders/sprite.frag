#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D texture_albedo;
uniform float emission;

// sprite variables //
uniform int framesInTexture;
uniform int currentFrame;
uniform bool flipX;
uniform bool flipY;
uniform vec4 color;

void main()
{
	vec2 UVcoords = UV;
	if(flipX)
	{
		UVcoords.x = 1.0 - UVcoords.x;
	}

	if(flipY)
	{
		UVcoords.y = 1.0 - UVcoords.y;
	}

	vec4 diffuse;
	if(framesInTexture == 1)
	{
		diffuse = texture(texture_albedo, UVcoords);
	}
	else
	{
		float frameSize = 1.0 / framesInTexture;
		float framePosition = frameSize * currentFrame;
		vec2 uv = vec2(UVcoords.x / framesInTexture + framePosition, UVcoords.y);
		diffuse = texture(texture_albedo, uv);
	}

	if(diffuse.a < 0.5)
	{
		discard;
	}

	if(color != vec4(0.0, 0.0, 0.0, 0.0))
	{
		diffuse.rgb *= color.rgb;

		FragColor = vec4(diffuse.rgb, color.a);
		BrightColor = vec4(diffuse.rgb * emission, 1.0);
		return;
	}
	
    
	FragColor = vec4(diffuse.rgb, 1.0);
	BrightColor = vec4(diffuse.rgb * emission, 1.0);
}