#include "precomp.h"
#include "ray.h"
#include "ListOfHittables.h"
#include "Sphere.h"
#include "Ellipsoid.h"
#include "camera.h"
#include "Diffuse.h"
#include "metal.h"
#include "dielectric.h"
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

namespace Tmpl8
{
	sceneLoader::sceneLoader()
	{

	}

	void sceneLoader::loadScene(ListOfHittables& world, int sceneIndex)
	{
		switch (sceneIndex)
		{
		case 0:
			world.AddToList(new Sphere(vec3(40.f, 20.f, 100.f), 40.f, new Diffuse(make_unique<imageTexture>("assets/dabuz.jpg"))));
			break;
		case 1:
			//SphereFlake
			world.AddToList(new Sphere(vec3(140.f, 40.f, 140.f), 10.f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
			makeFlake(vec3(140.f, 40.f, 140.f), m_maxFlakeDepth, 10.f, world);
			break;
		case 2:
			//Big scene 
			for (int i = 0; i < 300; i++)
			{
				for (int j = 0; j < 300; j++)
				{
					world.AddToList(new Sphere(vec3(static_cast<float>(i), 0.f, static_cast<float>(j) - 0.f), 0.5f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
					//world.AddToList(new Ellipsoid(vec3(i, 2.0f, j - 0.f), vec3(1.f, 1.f + 0.2f * i, 1.f), 0.5f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
				}
			}
			break;
		case 3:
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					world.AddToList(new Ellipsoid(vec3(2.f * i, 0.f, j * 2.f), vec3(1.f, 1.f + 0.2f * i, 1.f), 1.f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
				}
			}
			break;
		case 4: 
		
			world.AddToList(new Sphere(vec3(10.f, 7.5f, 20.f), 5.f, new dielectric(refractAcryl)));
			world.AddToList(new Ellipsoid(vec3(10.f, 1.5f, 20.f), vec3(5.f, 1.f, 5.f), 1.f, new Diffuse(vec3(1.f, 0.f, 0.5f))));
			world.AddToList(new Ellipsoid(vec3(10.f, -249.5f, 20.f), vec3(10.f, 250.f, 5.f), 1.f, new Diffuse(vec3(1.f, 0.f, 0.5f))));
			//RefractionIndex 1 is purposefully done here to get a transparant sphere that still has Beer's law. This is not a visual bug. 
			world.AddToList(new Sphere(vec3(50.f, -40.f, 200.f), 10.f, new dielectric(1.f)));
			makeFlake(vec3(50.f, -40.f, 200.f), 3, 10.f, world);

			break;
		default: assert(0);
		}
	}

	void sceneLoader::makeFlake(vec3 center, int flakeDepth, float radius, ListOfHittables& world)
	{
		if (flakeDepth > 0)
		{
			if (flakeDepth % 3 == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					float angle = i * 0.5f * PI;
					vec3 vectorToPoint = vec3(cos(angle), sin(angle), 0.f);
					vec3 l_center = center + vectorToPoint * radius * 1.5f;
					world.AddToList(new Sphere(l_center, radius * 0.5f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
					makeFlake(l_center, flakeDepth - 1, radius * 0.5f, world);
				}
			}
			else if (flakeDepth % 3 == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					float angle = i * 0.5f * PI;
					vec3 vectorToPoint = vec3(cos(angle), 0.f, sin(angle));
					vec3 l_center = center + vectorToPoint * radius * 1.5f;
					world.AddToList(new Sphere(l_center, radius * 0.5f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
					makeFlake(l_center, flakeDepth - 1, radius * 0.5f, world);
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					float angle = i * 0.5f * PI;
					vec3 vectorToPoint = vec3(0.f, sin(angle), cos(angle));
					vec3 l_center = center + vectorToPoint * radius * 1.5f;
					world.AddToList(new Sphere(l_center, radius * 0.5f, new Diffuse(vec3(randomFloat(), randomFloat(), randomFloat()))));
					makeFlake(l_center, flakeDepth - 1, radius * 0.5f, world);
				}
			}
		}
	}
}