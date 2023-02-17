#include "Game/Enemy.h"
#include "Game/EnemyDeathEffect.h"
#include "Game/DamageTextEffect.h"

#include "Engine/Utilities.h"
#include "Engine/Audio.h"
#include "Engine/BoxCollider.h"
#include "Engine/Camera.h"
#include "Graphics/SpriteRenderer.h"

#include <string>

Enemy::Enemy(Transform* playerTransform) : playerTransform(playerTransform)
{
	std::string path = "enemy1.png";

	enemyRenderer = new SpriteRenderer(path, &transform, 4, 1000.0f);
	enemyRenderer->SetAnimationStride(0, 0, 100.0f);

	eyeRenderer = new SpriteRenderer("playerEyes.png", &eyeTransform);

	collider = new BoxCollider((GameObject*)this, glm::vec2(0.3, 0.3), "enemy");
	eyeRenderer->Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	eyeRenderer->Emission = 0.0f;
}

Enemy::~Enemy()
{
	collider->Remove();
}

void Enemy::Update(float deltaTime)
{
	glm::vec3 dir = playerTransform->Position - transform.Position;
	glm::vec3 eyePos = glm::normalize(playerTransform->Position - transform.Position) * eyeFollowMax;

	enemyRenderer->FlipX = dir.x < 0;
	eyeRenderer->FlipX = dir.x < 0;

	if(dir.x < 0.0f)
	{
		eyePos.x -= eyeOffset.x;
	}

	eyeTransform.Position = transform.Position + eyePos + eyeOffset;
	eyeTransform.Position.z = 0.01f;

	hitEffectTimer += deltaTime;
	damageTimer += deltaTime;

	if(hitEffectTimer < hitEffectDuration)
	{
		enemyRenderer->ColorOverwrite = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		enemyRenderer->ColorOverwriteEnabled = true;

		eyeRenderer->ColorOverwrite = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		eyeRenderer->ColorOverwriteEnabled = true;
	}
	else
	{
		enemyRenderer->ColorOverwriteEnabled = false;
		eyeRenderer->ColorOverwriteEnabled = false;
	}

	walkAnimTimer += walkAnimSpeed * deltaTime;
	if(glm::length(dir) > meleeRange)
	{
		transform.Position += glm::normalize(dir) * movementSpeed * deltaTime;
		transform.Rotation.z = cosf(walkAnimTimer) * walkAnimAngle;
	}
	else
	{
		walkAnimTimer = 0.0f;
		transform.Rotation.z = Lerp(transform.Rotation.z, 0.0f, walkResetSpeed * deltaTime);
	}

	eyeTransform.Rotation.z = transform.Rotation.z;
	lastDeltaTime = deltaTime;
}

void Enemy::Draw(Camera* camera)
{
	enemyRenderer->Draw(camera);
	eyeRenderer->Draw(camera);
}

void Enemy::OnCollision(const std::string& tag, GameObject* obj)
{
	if(damageTimer > damageCooldown)
	{
		if(tag == "bullet")
		{
			health--;
			enemyRenderer->Emission -= 0.15f;

			int randomDamageTemp = RandomInRange(3, 8);
			DamageTextEffect* effect = new DamageTextEffect(randomDamageTemp, transform.Position);

			hitEffectTimer = 0.0f;

			int randomSprite = RandomInRange(1, 4);
			std::string path = "enemyHit" + std::to_string(randomSprite) + ".wav";
			Audio::PlaySound("enemyHit.wav");

			if(obj != nullptr)
			{
				obj->DeleteGameObject();
			}
		}

		if(tag == "fist")
		{
			health--;
			enemyRenderer->Emission -= 0.15f;

			damageTimer = 0.0f;
			hitEffectTimer = 0.0f;

			int randomDamageTemp = RandomInRange(7, 21);
			DamageTextEffect* effect = new DamageTextEffect(randomDamageTemp, transform.Position);

			int randomSprite = RandomInRange(1, 4);
			std::string path = "enemyHit" + std::to_string(randomSprite) + ".wav";
			Audio::PlaySound("enemyHit.wav");
		}

		if(health <= 0)
		{
			Audio::PlaySound("death.wav");
			Camera::ApplyScreenshake(0.1f, 0.12f);
			EnemyDeathEffect* effect = new EnemyDeathEffect(transform.Position, playerTransform->Position, 1);
			DeleteGameObject();
		}

		// 5 is max health
		float h = (float)health / (float)maxHealth;
		float p = 1.0f - h;
		int frame = (int)(4.0f * p);
		enemyRenderer->SetAnimationStride(frame, frame, 100.0f);
		eyeRenderer->Color = Lerp(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), p * 1.5f);
		eyeRenderer->Emission = Lerp(0.0f, 5.0f, p);
	}

	if(tag == "enemy")
	{
		if(obj != nullptr)
		{
			glm::vec3 dir = glm::normalize(transform.Position - obj->transform.Position);
			transform.Position += dir * avoidance * lastDeltaTime;
		}
	}
}
