#pragma once
#include "GameSystems/GameObject.h"
#include <vector>
#include "Engine/Audio.h"

class SpriteRenderer;
class BoxCollider;

class PanicButton : public GameObject
{
public:
	PanicButton();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(BoxCollider* collider);

	bool pressed = false;

private:
	SpriteRenderer* buttonSprite;
	SpriteRenderer* buttonPressedSprite;
	BoxCollider* collider;

	float announcementTime = 5.0f;
	float timer = 0.0f;
	bool playedMusic = false;
	float t = 1.35f;

	std::vector<Transform> droppingBlocks;
	SpriteRenderer* block;
	Transform blockTransform;
	float blockFallSpeed = 24.0f;
	float blockRotationSpeed = 650.0f;

};