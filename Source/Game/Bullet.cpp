#include "Bullet.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Engine/Utilities.h"
#include "../Engine/BoxCollider.h"

Bullet::Bullet(glm::vec3 direction, float speed, float lifeTime, float spread) :
	speed(speed), lifeTime(lifeTime), spread(spread)
{
	if(spread > 0.0f)
	{
		glm::vec3 dir = direction;
		dir.x = dir.x + RandomInRange(-spread, spread);
		dir.y = dir.y + RandomInRange(-spread, spread);
		this->direction = glm::normalize(dir);
	}
	else
	{
		this->direction = glm::normalize(direction);
	}

	spriteRenderer = new SpriteRenderer("bullet.png", &transform);
	collider = new BoxCollider((GameObject*)this, glm::vec2(0.1f, 0.1f), "bullet");

	transform.Rotation.z = RandomInRange(0.0f, 360.0f);
	zRotationSpeed = RandomInRange(1040.0f, 2080.0f);
}

Bullet::~Bullet()
{
	collider->Remove();
	//delete spriteRenderer;
}

void Bullet::Update(float deltaTime)
{
	lifeTime -= deltaTime;

	if(lifeTime < 0.0f)
	{
		DeleteGameObject();
	}

	transform.Position += (direction * speed) * deltaTime;
	spriteRenderer->Color = Color;
	spriteRenderer->Emission = Emission;

	transform.Rotation.z += zRotationSpeed * deltaTime;
	transform.Scale = glm::vec3(BulletSize);
}

void Bullet::Draw(Camera* camera)
{
	spriteRenderer->Draw(camera);
}