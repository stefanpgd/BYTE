#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = delete;
	Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);

	void Update(float deltaTime);

	glm::mat4& GetViewProjectionMatrix();
	float GetNearClip();
	float GetFarClip();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewProjectionMatrix;

	float windowWidth;
	float windowHeight;

	float cameraMovespeed = 5.0f;

	float FOV = 45.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;

	float nearClip = 0.1f;
	float farClip = 10000.0f;

	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;
	bool firstMouseMovement = true;
	bool constrainPitch = true;
};