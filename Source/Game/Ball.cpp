#include "Ball.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/Utilities.h"
#include "Engine/BoxCollider.h"

#include <imgui.h>

Ball::Ball()
{
	ballSprite = new SpriteRenderer("ball.png", &transform);
	ballHitSprite = new SpriteRenderer("ball_bounce.png", &transform);
	collider = new BoxCollider(this, glm::vec2(0.5), "ball");

	transform.Position.y = -2.0f;
	transform.Scale = glm::vec3(1.2f);

	moveDirection.x = RandomInRange(-1.0f, 1.0f);
	moveDirection.y = -0.5f;
	moveDirection.z = 0.0f;

	moveDirection = glm::normalize(moveDirection);
}

void Ball::Update(float deltaTime)
{
	if (firstBounce)
	{
		transform.Position += moveDirection * 8.0f * deltaTime;
	}
	else
	{
		transform.Position += moveDirection * moveSpeed * deltaTime;
	}

	transform.Rotation.z += rotationSpeed * deltaTime;

	hitTimer += deltaTime;
	hitSpriteTimer += deltaTime;

	if (hitTimer > hitCooldown)
	{
		// Left Wall //
		if (transform.Position.x < -mapX)
		{
			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
		}

		// Right Wall //
		if (transform.Position.x > mapX)
		{
			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(-1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
		}

		// Top Wall //
		if (transform.Position.y > mapTop)
		{
			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, -1.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
		}

		// Void // 
		if (transform.Position.y < mapBottom)
		{
			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, 1.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
		}
	}
}

void Ball::Draw(Camera* camera)
{
	if (hitSpriteTimer < hitSpriteDelay)
	{
		ballHitSprite->Draw(camera);
	}
	else
	{
		ballSprite->Draw(camera);
	}
}

void Ball::OnCollision(BoxCollider* collider)
{
	if (collider->Tag == "player")
	{
		Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength, moveDirection);
		moveDirection.y *= -1;
		hitTimer = 0.0f;
		hitSpriteTimer = 0.0f;

		glm::vec3 playerPos = collider->GetOwner()->transform.Position;
		playerPos.y -= 0.5f;

		glm::vec3 dir = transform.Position - playerPos;
		dir.y = 0.3f;
		dir = glm::normalize(dir);

		printf("dir: %f %f\n", dir.x, dir.y);

		moveDirection.x = dir.x;
		firstBounce = false;
	}

	if (collider->Tag == "block")
	{
		glm::vec3 blockPosition = collider->GetOwner()->transform.Position;

		// Hit Bottom //
		if (transform.Position.y < blockPosition.y - 1.0f)
		{
			collider->GetOwner()->DeleteGameObject();

			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, -1.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);

			moveSpeed += speedIncreasePerBlock;
			return;
		}

		// Hit Top // 
		if (transform.Position.y > blockPosition.y + 1.0f)
		{
			collider->GetOwner()->DeleteGameObject();

			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(0.0f, 1.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
			moveSpeed += speedIncreasePerBlock;

			return;
		}

		if (transform.Position.x > blockPosition.x + 2.0f)
		{
			collider->GetOwner()->DeleteGameObject();

			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
			moveSpeed += speedIncreasePerBlock;

			return;
		}

		if (transform.Position.x < blockPosition.x - 2.0f)
		{
			collider->GetOwner()->DeleteGameObject();

			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;

			moveDirection = glm::reflect(moveDirection, glm::vec3(-1.0f, 0.0f, 0.0f));
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
			moveSpeed += speedIncreasePerBlock;

			return;
		}
	}
}

void Ball::ImGuiDraw()
{
	ImGui::Begin("Ball");
	ImGui::DragFloat3("Position", &transform.Position[0]);
	ImGui::End();
}