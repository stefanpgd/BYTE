#include "UIRenderer.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Renderer.h"
#include "UISystem.h"

#include <imgui.h>

UIRenderer::UIRenderer(const std::string& fileName)
{
	this->fileName = fileName;

	quad = new Model("Quad/Quad.gltf", &transform);
	shaderProgram = new ShaderProgram("ui.vert", "ui.frag");
	texture = new Texture(fileName, TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);

	screenWRep = 1.0f / Renderer::GetWindowWidth();
	screenHRep = 1.0f / Renderer::GetWindowHeight();

	UISystem::AddUIRenderer(this);
}

void UIRenderer::Draw()
{
	transform.Position = glm::vec3(Position.x, Position.y, 0.0f);

	glm::vec3 scale;
	scale.x = (texture->GetWidth() * screenWRep) * Size.x;
	scale.y = (texture->GetHeight() * screenHRep) * Size.y;
	scale.z = 1.0f;

	transform.Scale = scale;

	glDisable(GL_DEPTH_TEST);
	shaderProgram->Bind();
	texture->Bind(shaderProgram);
	quad->Draw(shaderProgram);
	glDisable(GL_DEPTH_TEST);
}

void UIRenderer::ImGuiDraw()
{
	std::string windowName = "UI Element - " + fileName;

	ImGui::Begin(windowName.c_str());
	ImGui::DragFloat2("Position", &Position[0], 0.001f, -1.0f, 1.0f);
	ImGui::DragFloat2("Size", &Size[0], 0.001f);
	ImGui::End();
}