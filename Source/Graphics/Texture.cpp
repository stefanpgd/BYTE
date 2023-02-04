#include "Graphics/Texture.h"

#include "Graphics/ShaderProgram.h"

#include <cassert>
#include <stb_image.h>

Texture::Texture(const std::string& path, TextureType type, bool loadSRGB, int wrapMode, int mipmapMode)
{
	this->type = type;
	std::string filePath = "Assets/Textures/" + path;

	buffer = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

	if(buffer == nullptr)
	{
		assert(false && "Failed to load texture.");
	}

	// Generate a texture ID to use
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mipmapMode);

	unsigned int format = channels == 3 ? GL_RGB : GL_RGBA;

	if(loadSRGB)
	{
		unsigned int sRGBFormat = channels == 3 ? GL_SRGB : GL_SRGB_ALPHA;
		glTexImage2D(GL_TEXTURE_2D, 0, sRGBFormat, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(buffer);
}

void Texture::Bind(const ShaderProgram* program)
{
	unsigned int typeValue = (unsigned int)type;
	glActiveTexture(GL_TEXTURE0 + typeValue);
	glBindTexture(GL_TEXTURE_2D, ID);
	program->SetInt(bindNames[int(typeValue)], typeValue);
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}
