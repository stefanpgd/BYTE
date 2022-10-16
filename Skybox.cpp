#include "precomp.h"
#include "abstractHittable.h"
#include "RayTracingUtilities.h"
#include "solidColor.h"
#include "Skybox.h"

namespace Tmpl8
{
	Skybox::Skybox(const vec3& color) : albedoValue(std::move(make_unique<solidColor>(color)))
	{

	}

	static void GetSphereUV(float& u, float& v, const vec3& point)
	{
		float theta = acosf(-point.y);
		float fi = atan2f(-point.z, point.x) + PI;

		u = fi * 0.5f * dividedByPI;
		v = theta * dividedByPI;
	}

	Skybox::Skybox(unique_ptr<abstractTexture> color) : albedoValue(std::move(color))
	{

	}


	vec3 Skybox::getColor(float& u, float& v, vec3 point)
	{
		//Point here is the same as the outward normal since it's a normalized vector. 
		GetSphereUV(u, v, point);
		return albedoValue->colorValue(u, v, point);
	}

}