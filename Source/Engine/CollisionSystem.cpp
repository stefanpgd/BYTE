#include "CollisionSystem.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "../Game/GameObject.h"

void CollisionSystem::Update()
{
	for(BoxCollider* boxA : boxColliders)
	{
		// Skip static colliders //
		if(!boxA->IsStatic)
		{
			for(BoxCollider* boxB : boxColliders)
			{
				if(boxA != boxB)
				{
					CheckCollision(boxA, boxB);
				}
			}
		}
	}
}

void CollisionSystem::CheckCollision(BoxCollider* boxA, BoxCollider* boxB)
{
	glm::vec2 posA = boxA->gameObject ? boxA->gameObject->transform.Position : boxA->position;
	glm::vec2 posB = boxB->gameObject ? boxB->gameObject->transform.Position : boxB->position;

	if(posA.x < posB.x + boxB->Size.x)
	{
		if(posA.x + boxA->Size.x > posB.x)
		{
			if(posA.y < posB.y + boxB->Size.y)
			{
				if(posA.y + boxA->Size.y > posB.y)
				{
					boxA->gameObject->OnCollision(boxB->Tag);
				}
			}
		}
	}
}

void CollisionSystem::AddBoxCollider(BoxCollider* collider)
{
	boxColliders.push_back(collider);
}