#pragma once
#include <vector>

class BoxCollider;

class CollisionSystem
{
public:
	void Update();

	static void AddBoxCollider(BoxCollider* collider);

private:
	void CheckCollision(BoxCollider* boxA, BoxCollider* boxB);

	static inline std::vector<BoxCollider*> boxColliders;
};