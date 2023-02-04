#include "Engine/CollisionSystem.h"
#include "Engine/BoxCollider.h"
#include "Engine/Camera.h"

#include "Graphics/SpriteRenderer.h"
#include "Game/GameObject.h"

#include <glad/glad.h>
#include <imgui.h>

CollisionSystem::CollisionSystem()
{
	boxRenderer = new SpriteRenderer("blank.png", &transform);

	boxRenderer->Color = glm::vec4(0.1f, 1.0f, 0.1f, 0.1f);
}

void CollisionSystem::Update()
{
	boxColliders.erase(std::remove_if(boxColliders.begin(), boxColliders.end(),
		[](BoxCollider* box)
		{
			if(box->markedForDelete)
			{
				delete box;
				return true;
			}
			return false;
		}), boxColliders.end());

	for(BoxCollider* boxA : boxColliders)
	{
		// Skip static colliders //
		if(!boxA->IsStatic && boxA->IsActive)
		{
			for(BoxCollider* boxB : boxColliders)
			{
				if(boxA != boxB && boxB->IsActive)
				{
					CheckCollision(boxA, boxB);
				}
			}
		}
	}
}

void CollisionSystem::CheckCollision(BoxCollider* boxA, BoxCollider* boxB)
{
	// These are the centers of the boxes  //
	glm::vec2 posA = boxA->gameObject ? boxA->gameObject->transform.Position : boxA->Position;
	glm::vec2 posB = boxB->gameObject ? boxB->gameObject->transform.Position : boxB->Position;

	if(posA.x - boxA->Size.x < posB.x + boxB->Size.x)
	{
		if(posA.x + boxA->Size.x > posB.x - boxB->Size.x)
		{
			if(posA.y - boxA->Size.y < posB.y + boxB->Size.y)
			{
				if(posA.y + boxA->Size.y > posB.y - boxB->Size.y)
				{
					if(boxA->gameObject != nullptr)
					{
						boxA->gameObject->OnCollision(boxB->Tag, boxB->gameObject);
					}
				}
			}
		}
	}
}

void CollisionSystem::AddBoxCollider(BoxCollider* collider)
{
	boxColliders.push_back(collider);
}

void CollisionSystem::Draw(Camera* camera)
{
#if _DEBUG
	glEnable(GL_BLEND);
	for(BoxCollider* collider : boxColliders)
	{
		if(collider->IsActive)
		{
			transform.Scale = glm::vec3(collider->Size.x * 2.0f, collider->Size.y * 2.0f, 1.0f);

			if(collider->gameObject != nullptr)
			{
				transform.Position = collider->gameObject->transform.Position;
			}
			else
			{
				transform.Position = collider->Position;
			}

			boxRenderer->Draw(camera);
		}
	}
	glDisable(GL_BLEND);
#endif
}