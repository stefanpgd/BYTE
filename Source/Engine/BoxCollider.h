#pragma once
#include <glm/glm.hpp>
#include <string>

class GameObject;

class BoxCollider
{
public:
	BoxCollider(GameObject* gameObject, glm::vec2 size, std::string tag = "default");
	BoxCollider(glm::vec3 position, glm::vec2 size, std::string tag = "default");
	
	GameObject* GetOwner();

	void Remove();

	std::string Tag;
	glm::vec2 Size;
	bool IsStatic = false;
	bool IsActive = true;

	glm::vec3 Position;

private:
	GameObject* gameObject;

	bool markedForDelete = false;

	friend class CollisionSystem;
};