#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = delete;
	Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);

	void Update(float deltaTime);

	static void ApplyScreenshake(float duration, float magnitude);

	glm::mat4& GetViewProjectionMatrix();
	float GetNearClip();
	float GetFarClip();

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;

	float FOV = 45.0f;

private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewProjectionMatrix;

	float windowWidth;
	float windowHeight;

	float nearClip = 0.1f;
	float farClip = 1000.0f;

	// Screenshake // 
	static inline float screenshakeTimer = 0.0f;
	static inline float screenshakeStrength = 0.0f;
};