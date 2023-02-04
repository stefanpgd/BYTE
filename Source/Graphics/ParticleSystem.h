#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Engine/Transform.h"

class Model;
class ShaderProgram;
class Camera;

struct Particle
{
	// Management //
	float LifeTime;

	// Shading //
	glm::vec3 Color;
	float Emission = 0.0f;

	// Position & Movement // 
	glm::vec3 Position;
	float Z;
	float Size;

	float MoveSpeed = 0.0f;
	float Drag = 0.0f;

private:
	glm::vec3 velocity;

	friend class ParticleSystem;
};

struct ParticleSystemSettings
{
	// have min-maxes for each value, allowing 
	// to randomly pick values in given range 
	Particle defaultParticle;
	Particle MinParticle;
	Particle MaxParticle;
	bool UseMinMax = false;

	unsigned int particlesPerSeconds;
	float duration;
	bool Loops = false;
};

class ParticleSystem
{
public:
	ParticleSystem(const ParticleSystemSettings& systemSettings, glm::vec3& spawnPosition);

	void Update(float deltaTime);
	void Draw(Camera* camera);

	void Activate();
	void Disable();

private:
	void SpawnDefaultParticle();
	void SpawnRangedParticle();

	std::vector<Particle> particles;
	Transform particleTransform;

	Model* quad;
	ShaderProgram* particlePipeline;
	ParticleSystemSettings systemSettings;

	glm::vec3& spawnPosition;

	bool isActive = false;
	bool completed = false;

	float particleSpawnTimer = 0.0f;
	float timeTillParticleSpawn = 0.0f;

	float runTime = 0.0f;
};