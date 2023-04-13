#include "Ball.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/Utilities.h"
#include "Engine/BoxCollider.h"

#include <imgui.h>

Ball::Ball()
{
	ballSprite = new SpriteRenderer("ball.png", &transform);
	collider = new BoxCollider(this, glm::vec2(0.5), "ball");

	transform.Scale = glm::vec3(1.2f);

	moveDirection.x = RandomInRange(-1.0f, 1.0f);
	moveDirection.y = -0.5f;
	moveDirection.z = 0.0f;

	moveDirection = glm::normalize(moveDirection);
}

void Ball::Update(float deltaTime)
{
	transform.Position += moveDirection * moveSpeed * deltaTime;
	transform.Rotation.z += rotationSpeed * deltaTime;

	hitTimer += deltaTime;

	if (hitTimer > hitCooldown)
	{
		// Left Wall //
		if (transform.Position.x < -mapX)
		{
			hitTimer = 0.0f;
			moveDirection = glm::reflect(moveDirection, glm::vec3(1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(0.04f, 0.15f, moveDirection);
		}

		// Right Wall //
		if (transform.Position.x > mapX)
		{
			hitTimer = 0.0f;
			moveDirection = glm::reflect(moveDirection, glm::vec3(-1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(0.04f, 0.15f, moveDirection);
		}

		if (transform.Position.y > mapTop)
		{
			hitTimer = 0.0f;
			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, -1.0f, 0.0f));
			Camera::ApplyScreenshake(0.04f, 0.15f, moveDirection);
		}

		if (transform.Position.y < mapBottom)
		{
			hitTimer = 0.0f;
			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, 1.0f, 0.0f));
			Camera::ApplyScreenshake(0.04f, 0.15f, moveDirection);
		}
	}
}

void Ball::Draw(Camera* camera)
{
	ballSprite->Draw(camera);
}

void Ball::OnCollision(BoxCollider* collider)
{
	if (collider->Tag == "player")
	{
		Camera::ApplyScreenshake(0.04f, 0.1f, moveDirection);
		moveDirection.y *= -1;
	}
}

void Ball::ImGuiDraw()
{
	ImGui::Begin("Ball");
	ImGui::DragFloat3("Position", &transform.Position[0]);
	ImGui::End();
}