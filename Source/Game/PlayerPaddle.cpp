#include "PlayerPaddle.h"

#include "Graphics/SpriteRenderer.h"
#include "Engine/Input.h"
#include "Engine/Utilities.h"
#include "Engine/BoxCollider.h"

#include <imgui.h>

PlayerPaddle::PlayerPaddle()
{
	sprite = new SpriteRenderer("paddle.png", &transform);
	collider = new BoxCollider(this, glm::vec2(2.5, 0.5), "player");

	transform.Position.y = -14.0f;
	transform.Scale.x = 5.4375;
}

void PlayerPaddle::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputResponse * deltaTime);

	transform.Position.x += horizontalInput * paddleSpeed * deltaTime;
	transform.Position.x = glm::clamp(transform.Position.x, -boundary, boundary);
}

void PlayerPaddle::Draw(Camera* camera)
{
	sprite->Draw(camera);
}

void PlayerPaddle::OnCollision(BoxCollider* collider)
{
}

void PlayerPaddle::ImGuiDraw()
{
	ImGui::Begin("Paddle");
	ImGui::DragFloat3("Position", &transform.Position[0]);
	ImGui::End();
}