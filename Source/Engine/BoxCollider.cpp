#include "BoxCollider.h"
#include "CollisionSystem.h"

BoxCollider::BoxCollider(GameObject* obj, glm::vec2 size, std::string tag) :
	gameObject(obj), Size(size), Tag(tag)
{
	CollisionSystem::AddBoxCollider(this);
}

// Colliders with a position are considered static by default //
BoxCollider::BoxCollider(glm::vec3 position, glm::vec2 size, std::string tag) :
	position(position), Size(size), Tag(tag)
{
	IsStatic = true;
	CollisionSystem::AddBoxCollider(this);
}

void BoxCollider::Remove()
{
	markedForDelete = true;
}