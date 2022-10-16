#include "precomp.h"
#include "game.h"
#include "ray.h"
#include "ListOfHittables.h"
#include "Sphere.h"
#include "Ellipsoid.h"
#include "camera.h"
#include "Diffuse.h"
#include "metal.h"
#include "dielectric.h"
#include <Windows.h>
#include "RayTracingUtilities.h"
#include "abstractTexture.h"
#include "solidColor.h"
#include "checkerBoard.h"
#include "circularWaves.h"
#include "imageTexture.h"
#include "pointLight.h"
#include "areaLight.h"
#include "BVH.h"
#include "scene.h"
#include "Skybox.h"
#include <thread>
#include <mutex>
#include <condition_variable>

namespace Tmpl8
{
	std::condition_variable condition;
	std::vector<std::thread> workers;
	std::mutex mutsex;
	bool TraceRays = true;
	const int amountOfThreads = 12;
	bool threadChecks[amountOfThreads] = { false };
	const int threadSnippet = static_cast<int>(ScreenWidth / static_cast<float>(amountOfThreads));

	abstractLight* lights[numberOfLights];
	Skybox skybox = Skybox(make_unique<imageTexture>("assets/lakeside.jpg"));

	vec3 rayColor(const ray& r, ListOfHittables& world, int depth)
	{
		hitRecordStruct hitRecord;
		if (depth <= 0) return vec3(0.f);
		if (world.hit(r, hitRecord, 0.001f, infinity))
		{
			ray scatteredRay;
			vec3 attenuation;
			if (hitRecord.p_material->diffuseCheck())
			{
				//Random light based on the probability theory. 
				int randomLight = rand() % numberOfLights;
				vec3 lightPosition = lights[randomLight]->getPosition();
				vec3 shadowDirection = (lightPosition - hitRecord.point).normalized();
				ray shadowRay(hitRecord.point, shadowDirection * hitRecord.scaling);
				float shadowRayLengthSqr =
					((lightPosition.x - hitRecord.point.x) * (lightPosition.x - hitRecord.point.x) +
						(lightPosition.y - hitRecord.point.y) * (lightPosition.y - hitRecord.point.y) +
						(lightPosition.z - hitRecord.point.z) * (lightPosition.z - hitRecord.point.z));

				if (world.hit(shadowRay, hitRecord, 0.01f, sqrt(shadowRayLengthSqr)))
				{
					
					return 0;
					
				}
				hitRecord.p_material->scatterRay(r, hitRecord, attenuation, scatteredRay);

				return attenuation * lights[randomLight]->Attenuation(shadowRayLengthSqr, hitRecord, shadowDirection);

			}
			else if (hitRecord.p_material->scatterRay(r, hitRecord, attenuation, scatteredRay))
			{
				return attenuation * rayColor(scatteredRay, world, depth - 1);
			}
		}

		float u, v;
		return skybox.getColor(u, v, r.m_direction);
	}

	//Not a fan of these statics, but with the way I have currently set up my code it is fine. 

	ListOfHittables world;
	ListOfHittables realWorld;
	sceneLoader loader;
	camera rtCamera(60.f, vec3(-15.f, 11.f, 30.f), vec3(10.f, 6.f, 10.f), vec3(0.f, -1.f, 0.f), (vec3(3.f, 3.f, 2.f) - vec3(0.f, 0.f, -1.f)).sqrLentgh());

	void Game::doRayTracing(int startX, int endX, int startY, int endY)
	{
		while (TraceRays)
		{
			for (int j = endY - 1; j >= startY; j--)
			{
				for (int i = startX; i < endX; i++)
				{
					float u = static_cast<float>(i + seededRandomFloat(seedPointer)) / (ScreenWidth - 1);
					float v = 1 - static_cast<float>(j + seededRandomFloat(seedPointer)) / (ScreenHeight - 1);						
					ray r = rtCamera.getRay(u, v);
					savedColors[i + (ScreenHeight - 1 - j) * ScreenWidth] += rayColor(r, realWorld, maxDepth);
				}
			}
			int checkVar = startX / threadSnippet;
			threadChecks[checkVar] = true;

			//Wait in a mutex uses a spin lock. Not ideal but don't really have the time to change this. 
			std::unique_lock<std::mutex> lock(mutsex);
			condition.wait(lock);
		}
	}

	void Game::Init()
	{
		tSeed = static_cast<int>(time(NULL));
		seedPointer = &tSeed;

		red = 0;
		green = static_cast<int>(numberE);
		blue = 255;
		color = ((red << 16) + (green << 8) + blue);
		savedColors = new vec3[ScreenWidth * ScreenHeight];
		std::memset(savedColors, 0, ScreenWidth * ScreenHeight * sizeof(vec3));
		

		lights[0] = new areaLight(vec3(8.f, 2.f, 8.f), vec3(12.f, 8.f, 8.f), vec3(1.f, 1.f, 1.f), 100.f);
		lights[1] = new areaLight(vec3(50.f, -60.f, 180.f), vec3(50.f, -20.f, 180.f), vec3(1.f, 1.f, 1.f), 100.f);

		loader.loadScene(world, 4);

		realWorld.AddToList(new BVH(world));

		//Multithreading code 

		for (int i = 0; i < amountOfThreads; i++)
		{
			workers.emplace_back(std::thread([this, i]
				{doRayTracing(i * threadSnippet, (i * threadSnippet) + threadSnippet, 0, ScreenHeight); }));
		}
	}


	void Game::Shutdown()
	{
		TraceRays = false;
		condition.notify_all();
		for (int i = 0; i < amountOfThreads; i++)
		{
			workers[i].join();
		}
	}

	void Game::Tick(float deltaTime)
	{
		if (debugRays)
		{
			POINT mousePos;
			GetCursorPos(&mousePos);
			ray r = rtCamera.getRay(static_cast<float>(mousePos.x) / static_cast<float>((ScreenWidth - 1)), static_cast<float>(ScreenHeight - mousePos.y) / static_cast<float>(ScreenHeight - 1));
			vec3 pixelColor = rayColor(r, realWorld, maxDepth);
			color = ((static_cast<int>(sqrt(pixelColor.x) * 255.999f) << 16) + (static_cast<int>(sqrt(pixelColor.y) * 255.999f) << 8) + static_cast<int>(sqrt(pixelColor.z) * 255.999f));
			if (GetAsyncKeyState(VK_SPACE))
			{
				screen->Plot(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), color);
			}
			pixelColor = 0;
		}
		else {

			if (currentSample < samples)
			{

				for (int k = 0; k < amountOfThreads; k++)
				{
					if (!threadChecks[k]) break;

					if (k == (amountOfThreads - 1))
					{


						currentSample++;
						float sampleDivide = 1.f / currentSample;


						for (int j = ScreenHeight - 1; j >= 0; j--)
						{
							for (int i = 0; i < ScreenWidth; i++)
							{
								color = ((static_cast<int>(floatClamp(sqrt(savedColors[i + (ScreenHeight - 1 - j) * ScreenWidth].x * sampleDivide), 0, 1.f) * 255.999f) << 16)
									+ (static_cast<int>(floatClamp(sqrt(savedColors[i + (ScreenHeight - 1 - j) * ScreenWidth].y * sampleDivide), 0, 1.f) * 255.999f) << 8)
									+ static_cast<int>(floatClamp(sqrt(savedColors[i + (ScreenHeight - 1 - j) * ScreenWidth].z * sampleDivide), 0, 1.f) * 255.999f));
								screen->Plot(i, j, color);
							}
						}

						for (int h = 0; h < amountOfThreads; h++)
						{
							threadChecks[h] = false;
						}

						if (rtCamera.cameraMovement(deltaTime))
						{
							std::memset(savedColors, 0, ScreenWidth * ScreenHeight * sizeof(vec3));
							currentSample = 0;
						} 

						condition.notify_all();
					}
				}
			}
			else
			{
				TraceRays = false;
			}

		}
	}

};