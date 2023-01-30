#pragma once
#include <vector>
#include "Transform.h"

class BoxCollider;
class Camera;
class SpriteRenderer;

class CollisionSystem
{
public:
	CollisionSystem();

	void Update();
	void Draw(Camera* camera);

	static void AddBoxCollider(BoxCollider* collider);

private:
	void CheckCollision(BoxCollider* boxA, BoxCollider* boxB);

	static inline std::vector<BoxCollider*> boxColliders;

	Transform transform;
	SpriteRenderer* boxRenderer;
};