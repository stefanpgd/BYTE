#include "Ball.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/Utilities.h"
#include "Engine/BoxCollider.h"
#include "Engine/Audio.h"
#include "GameSystems/GameTime.h"

#include <imgui.h>
#include "Graphics/ParticleSystem.h"

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
	time += deltaTime;

	glm::vec3 discoColor = glm::cos(time + glm::vec3(0.0f, 2.0f, 4.0f)) * 0.5f + 0.5f;
	glm::vec3 col = glm::mix(glm::vec3(1.0f), discoColor, glm::clamp(ballSprite->Emission, 0.0f, 1.0f));
	ballSprite->Color = glm::vec4(col, 1.0f);
	ballHitSprite->Color = glm::vec4(col, 1.0f);

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

	for (ParticleSystem* pSystem : particleSystems)
	{
		pSystem->Update(deltaTime);
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

	for (ParticleSystem* pSystem : particleSystems)
	{
		pSystem->Draw(camera);
	}
}

void Ball::OnCollision(BoxCollider* collider)
{
	if (collider->GetOwner() == nullptr || collider->GetOwner()->markedForDelete)
	{
		return;
	}

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
			Audio::PlaySound("ballHit.wav");
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

void Ball::PanicMode()
{
	moveSpeed *= panicModeMultiplier;
	speedIncreasePerBlock *= panicModeMultiplier;
	maxSpeed *= panicModeMultiplier;
}

void Ball::Bounce(glm::vec3 normal)
{
	Audio::PlaySound("ballHit.wav");

	hitTimer = 0.0f;
	hitSpriteTimer = 0.0f;

	moveDirection = glm::reflect(moveDirection, glm::vec3(normal));
	Camera::ApplyScreenshake(bounceShakeDuration, bounceShakeStrength);
}

void Ball::BlockBounce(BoxCollider* collider, glm::vec3 normal)
{
	glm::vec3 blockPos = collider->GetOwner()->transform.Position;

	collider->GetOwner()->DeleteGameObject();
	Bounce(normal);
	moveSpeed += speedIncreasePerBlock;
	ballSprite->Emission += 0.03f;
	ballHitSprite->Emission += 0.03f;

	Camera::ApplyScreenshake(bounceShakeDuration * 1.5f, bounceShakeStrength * 2.0f);
	Audio::PlaySound("blockWave1.wav");

	ParticleSystemSettings settings;

	Particle pMin;
	pMin.Color = ballSprite->Color;
	pMin.Emission = ballSprite->Emission;
	pMin.LifeTime = 0.1f;
	pMin.MoveSpeed = 0.25f * moveSpeed;
	pMin.Size = 0.005 * moveSpeed;

	Particle pMax;
	pMax.Color = ballSprite->Color;
	pMax.Emission = ballSprite->Emission + 3.0f;
	pMax.LifeTime = 0.45f;
	pMax.MoveSpeed = 0.5f * moveSpeed;
	pMax.Size = 0.012 * moveSpeed;

	settings.UseMinMax = true;
	settings.MinParticle = pMin;
	settings.MaxParticle = pMax;
	settings.particlesPerSeconds = 5000;
	settings.duration = 0.07f;

	glm::vec3* pos = new glm::vec3(0.0f);
	*pos = transform.Position;
	ParticleSystem* system = new ParticleSystem(settings, *pos);
	system->Activate();
	particleSystems.push_back(system);
}