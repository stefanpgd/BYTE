#include "Graphics/TextRenderer.h"

#include "Engine/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Model.h"

TextRenderer::TextRenderer(const std::string& text, Transform* transform)
{
	this->text = text;
	this->transform = transform;

	quad = new Model("Quad/Quad.gltf", &letterTransform);
	textPipeline = new ShaderProgram("text.vert", "text.frag");

	std::string fontPath = "Fonts/pixelNumbers.png";
	font = new Texture(fontPath, TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);
}

void TextRenderer::Draw(Camera* camera)
{
	textPipeline->Bind();
	textPipeline->SetInt("framesInTexture", 11);
	textPipeline->SetFloat("emission", emission);
	textPipeline->SetVec4("color", color);
	font->Bind(textPipeline);
	letterTransform = *transform;

	for(int i = 0; i < text.size(); i++)
	{
		letterTransform.Position.x = transform->Position.x + (letterOffset * i) * transform->Scale.x;

		textPipeline->SetInt("currentFrame", GetFontPosition(text[i]));
		quad->Draw(textPipeline, camera);
	}
}

void TextRenderer::UpdateText(const std::string& text)
{
	this->text = text;
}

unsigned int TextRenderer::GetFontPosition(char c)
{
	unsigned int v = static_cast<unsigned int>(c);

	if(v >= 48 && v <= 57)
	{
		// is char value between 0 - 9 ( ASCII )
		return v - 48;
	}

	if (v == 58)
	{
		return 10;
	}

	return 0;
}