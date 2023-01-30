#include "BoxCollider.h"

BoxCollider::BoxCollider(Transform* transform, glm::vec2 size, std::string tag) :
	transform(transform), Size(size), Tag(tag)
{

}

// Colliders with a position are considered static by default //
BoxCollider::BoxCollider(glm::vec3 position, glm::vec2 size, std::string tag) :
	position(position), Size(size), Tag(tag)
{
	isStatic = true;
}