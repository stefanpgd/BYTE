#include "PlayerPaddle.h"

#include "Graphics/SpriteRenderer.h"
#include "Engine/Input.h"
#include "Engine/Utilities.h"

#include <imgui.h>

PlayerPaddle::PlayerPaddle()
{
	sprite = new SpriteRenderer("paddle.png", &transform);
	transform.Scale.x = 5.4375;
}

void PlayerPaddle::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputResponse * deltaTime);

	transform.Position.x += horizontalInput * paddleSpeed * deltaTime;
}

void PlayerPaddle::Draw(Camera* camera)
{
	sprite->Draw(camera);
}

void PlayerPaddle::ImGuiDraw()
{
	ImGui::Begin("Paddle");
	ImGui::DragFloat3("Position", &transform.Position[0]);
	ImGui::End();
}