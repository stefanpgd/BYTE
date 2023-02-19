#include "Engine/BoxCollider.h"
#include "Engine/CollisionSystem.h"

BoxCollider::BoxCollider(GameObject* obj, glm::vec2 size, std::string tag) :
	gameObject(obj), Size(size), Tag(tag)
{
	CollisionSystem::AddBoxCollider(this);
}

// Colliders with a position are considered static by default //
BoxCollider::BoxCollider(glm::vec3 position, glm::vec2 size, std::string tag) :
	Position(position), Size(size), Tag(tag)
{
	IsStatic = true;
	CollisionSystem::AddBoxCollider(this);
}

GameObject* BoxCollider::GetOwner()
{
	if (gameObject == nullptr)
	{
		printf("Error: Box Collider you are trying to retrieve the gameobject has NO gameobject attached to it\n");
		return nullptr;
	}

	return gameObject;
}

void BoxCollider::Remove()
{
	markedForDelete = true;
}