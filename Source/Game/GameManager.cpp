#include "GameManager.h"
#include "GameObject.h"
#include "../Engine/Camera.h"
#include "../Engine/Utilities.h"
#include "../Engine/Input.h"

#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"

Model* model;
Transform transform;
ShaderProgram* shader;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	
	model = new Model("Quad/Quad.gltf", &transform);
	shader = new ShaderProgram("color.vert", "color.frag");
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
}

void GameManager::Draw()
{
	shader->Bind();
	shader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	model->Draw(shader);
}

void GameManager::ImGuiDraw()
{
#if _DEBUG
	// Imgui Draw Calls
#endif
}