#include "Graphics/ParticleSystem.h"

#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Graphics/Model.h"
#include "Graphics/ShaderProgram.h"

ParticleSystem::ParticleSystem(const ParticleSystemSettings& systemSettings, glm::vec3& spawnPosition) : spawnPosition(spawnPosition)
{
	this->systemSettings = systemSettings;

	quad = new Model("Quad/Quad.gltf", &particleTransform);
	particlePipeline = new ShaderProgram("particle.vert", "particle.frag");

	timeTillParticleSpawn = 1.0f / systemSettings.particlesPerSeconds;
}

void ParticleSystem::Update(float deltaTime)
{
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[](Particle& particle) { return particle.LifeTime < 0.0f; }), particles.end());

	for(Particle& particle : particles)
	{
		particle.LifeTime -= deltaTime;

		particle.Position += particle.velocity * deltaTime;
		particle.velocity += particle.velocity * (-particle.Drag * deltaTime);
	}

	if(isActive && !completed)
	{
		particleSpawnTimer += deltaTime;

		if(particleSpawnTimer > timeTillParticleSpawn)
		{
			if(systemSettings.UseMinMax)
			{
				SpawnRangedParticle();
			}
			else
			{
				SpawnDefaultParticle();
			}

			particleSpawnTimer = 0.0f;
		}
	}

	runTime += deltaTime;
	if(isActive && !systemSettings.Loops)
	{
		if(runTime > systemSettings.duration)
		{
			completed = true;
		}
	}
}

void ParticleSystem::Draw(Camera* camera)
{
	particlePipeline->Bind();

	for(Particle& particle : particles)
	{
		particleTransform.Position = particle.Position;
		particleTransform.Position.z = particle.Z;
		particleTransform.Scale = glm::vec3(particle.Size);

		particlePipeline->SetVec3("color", particle.Color);
		particlePipeline->SetFloat("emission", particle.Emission);

		quad->Draw(particlePipeline, camera);
	}
}

void ParticleSystem::Activate()
{
	runTime = 0.0f;
	particleSpawnTimer = 0.0f;
	isActive = true;
	completed = false;
}

void ParticleSystem::Disable()
{
	isActive = false;
	completed = false;
}

void ParticleSystem::SpawnDefaultParticle()
{
	Particle particle = systemSettings.defaultParticle;
	particle.Position = spawnPosition;

	particle.velocity = glm::normalize(glm::vec3(RandomInRange(-1.0f, 1.0f), RandomInRange(-1.0f, 1.0f), 0.0f)) * particle.MoveSpeed;

	particles.push_back(particle);
}

void ParticleSystem::SpawnRangedParticle()
{
	Particle particle;
	particle.Position = spawnPosition;
	particle.Z = systemSettings.MinParticle.Z;

	particle.LifeTime = Lerp(systemSettings.MinParticle.LifeTime, systemSettings.MaxParticle.LifeTime, Random01());
	particle.Color = Lerp(systemSettings.MinParticle.Color, systemSettings.MaxParticle.Color, Random01());
	particle.Emission = Lerp(systemSettings.MinParticle.Emission, systemSettings.MaxParticle.Emission, Random01());
	particle.Size = Lerp(systemSettings.MinParticle.Size, systemSettings.MaxParticle.Size, Random01());
	particle.MoveSpeed = Lerp(systemSettings.MinParticle.MoveSpeed, systemSettings.MaxParticle.MoveSpeed, Random01());
	particle.Drag = Lerp(systemSettings.MinParticle.Drag, systemSettings.MaxParticle.Drag, Random01());

	particle.velocity = glm::normalize(glm::vec3(RandomInRange(-1.0f, 1.0f), RandomInRange(-1.0f, 1.0f), 0.0f)) * particle.MoveSpeed;
	particles.push_back(particle);
}