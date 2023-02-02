#pragma once
#include <string>
#include <glad/glad.h>

class ShaderProgram;

enum class TextureType
{
	Albedo = 0,
	Normal,
	MetalicRoughness,
	AmbientOcclusion,
	Emissive,
	Metallic,
	Roughness
};

class Texture
{
public:
	Texture(const std::string& filePath, TextureType type, bool loadSRGB = false, int wrapMode = GL_REPEAT, int mipmapMode = GL_LINEAR);
	
	void Bind(const ShaderProgram* program);

	int GetWidth();
	int GetHeight();

private:
	TextureType type;
	unsigned int ID;
	int width;
	int height;
	int channels;
	unsigned char* buffer;

	std::string bindNames[7]
	{
		"texture_albedo",
		"texture_normal",
		"texture_mr",
		"texture_ao",
		"texture_emissive",
		"texture_metallic",
		"texture_rougness"
	};
};