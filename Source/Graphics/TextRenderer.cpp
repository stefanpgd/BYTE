#include "TextRenderer.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "../Engine/Camera.h"

TextRenderer::TextRenderer(const std::string& fontName, Transform* transform)
{
	this->transform = transform;

	quad = new Model("Quad/Quad.gltf", this->transform);
	textPipeline = new ShaderProgram("text.vert", "text.frag");

	std::string fontPath = "Fonts/" + fontName;
	font = new Texture(fontPath, TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);
}

void TextRenderer::Draw(Camera* camera)
{
	textPipeline->Bind();

	font->Bind(textPipeline);
	quad->Draw(textPipeline, camera);
}

unsigned int TextRenderer::GetFontPosition(char c)
{
	return 0;
}