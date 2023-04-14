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
	moveDirection = glm::normalize(moveDirection);
	moveSpeed = glm::clamp(moveSpeed, 0.0f, maxSpeed);

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
			Bounce(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		// Right Wall //
		if (transform.Position.x > mapX)
		{
			Bounce(glm::vec3(-1.0f, 0.0f, 0.0f));
		}

		// Top Wall //
		if (transform.Position.y > mapTop)
		{
			Bounce(glm::vec3(0.0f, -1.0f, 0.0f));

		}

		// Void // 
		if (transform.Position.y < mapBottom)
		{
			Bounce(glm::vec3(0.0f, 1.0f, 0.0f));
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
		glm::vec3 playerPos = collider->GetOwner()->transform.Position;

		if (transform.Position.y > playerPos.y + 0.15f)
		{
			glm::vec3 playerScale = collider->GetOwner()->transform.Scale;
			glm::vec3 moveDir = glm::vec3(0.0f, 1.0f, 0.0f);

			float x = transform.Position.x - playerPos.x;
			float weight = x / (playerScale.x / 2);
			weight = glm::clamp(weight, -1.0f, 1.0f);

			moveDir.x = weight * paddleSteerStrength;
			moveDirection = moveDir;

			firstBounce = false;
			hitTimer = 0.0f;
			hitSpriteTimer = 0.0f;
			Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength, moveDirection);
		}
	}

	if (collider->Tag == "block")
	{
		if (hitTimer < hitCooldown)
		{
			return;
		}

		glm::vec3 blockPosition = collider->GetOwner()->transform.Position;

		// Hit Bottom //
		if (transform.Position.y < blockPosition.y - 1.0f)
		{
			BlockBounce(collider, glm::vec3(0.0f, -1.0f, 0.0f));
			return;
		}

		// Hit Top // 
		if (transform.Position.y > blockPosition.y + 1.0f)
		{
			BlockBounce(collider, glm::vec3(0.0f, 1.0f, 0.0f));
			return;
		}

		if (transform.Position.x > blockPosition.x + 2.0f)
		{
			BlockBounce(collider, glm::vec3(1.0f, 0.0f, 0.0f));
			return;
		}

		if (transform.Position.x < blockPosition.x - 2.0f)
		{
			BlockBounce(collider, glm::vec3(-1.0f, 0.0f, 0.0f));
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

void Ball::Bounce(glm::vec3 normal)
{
	hitTimer = 0.0f;
	hitSpriteTimer = 0.0f;

	moveDirection = glm::reflect(moveDirection, glm::vec3(normal));
	Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
}

void Ball::BlockBounce(BoxCollider* collider, glm::vec3 normal)
{
	collider->GetOwner()->DeleteGameObject();
	Bounce(normal);
	moveSpeed += speedIncreasePerBlock;
}