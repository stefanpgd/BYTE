#pragma once
#include <glm/glm.hpp>
#include <string>

class Transform;

class BoxCollider
{
public:
	BoxCollider(Transform* transform, glm::vec2 size, std::string tag = "default");

	BoxCollider(glm::vec3 position, glm::vec2 size, std::string tag = "default");

	std::string Tag;
	glm::vec2 Size;
	bool isStatic = false;

private:
	Transform* transform;
	glm::vec3 position;

	friend class CollisionSystem;
};