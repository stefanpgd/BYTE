#include "Enemy.h"

#include "../Engine/Utilities.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Engine/BoxCollider.h"

#include <string>

Enemy::Enemy(Transform* playerTransform) : playerTransform(playerTransform)
{
	int randomSprite = RandomInRange(1, 4);
	std::string path = "enemy" + std::to_string(randomSprite) + ".png";

	enemyRenderer = new SpriteRenderer(path, &transform);
	eyeRenderer = new SpriteRenderer("playerEyes.png", &eyeTransform);

	collider = new BoxCollider((GameObject*)this, glm::vec2(0.3, 0.3), "enemy");
	eyeRenderer->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	eyeRenderer->Emission = 1.5f;
}

Enemy::~Enemy()
{
	collider->Remove();
}

void Enemy::Update(float deltaTime)
{
	glm::vec3 eyePos = glm::normalize(playerTransform->Position - transform.Position) * eyeFollowMax;
	eyeTransform.Position = transform.Position + eyePos + eyeOffset;
	eyeTransform.Position.z = 0.01f;

	hitEffectTimer += deltaTime;

	if (hitEffectTimer < hitEffectDuration)
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
}

void Enemy::Draw(Camera* camera)
{
	enemyRenderer->Draw(camera);
	eyeRenderer->Draw(camera);
}

void Enemy::OnCollision(const std::string& tag, GameObject* obj)
{
	if(tag == "bullet")
	{
		health--;
		hitEffectTimer = 0.0f;

		if(obj != nullptr)
		{
			obj->DeleteGameObject();
		}

		if(health <= 0)
		{
			DeleteGameObject();
		}
	}
}
