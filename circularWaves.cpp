#include "precomp.h"
#include "circularWaves.h"
#include "abstractHittable.h"
#include "RayTracingUtilities.h"
#include "solidColor.h"

namespace Tmpl8
{
	circularWaves::circularWaves(unique_ptr<abstractTexture> evenColor, unique_ptr<abstractTexture> unevenColor) : even(std::move(evenColor)), uneven(std::move(unevenColor))
	{

	}

	circularWaves::circularWaves(vec3 evenColor, vec3 unevenColor) : even(make_unique<solidColor>(evenColor)), uneven(make_unique<solidColor>(unevenColor))
	{

	}

	vec3 circularWaves::colorValue(float u, float v, vec3& point)
	{
	
		float sines = sin(100.f * point.y);
		if (sines < 0)
			return uneven->colorValue(u, v, point);

		return even->colorValue(u, v, point);
	}
}