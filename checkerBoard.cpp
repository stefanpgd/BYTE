#include "precomp.h"
#include "abstractHittable.h"
#include "RayTracingUtilities.h"
#include "checkerBoard.h"
#include "solidColor.h"

namespace Tmpl8 {

	checkerBoard::checkerBoard(unique_ptr<abstractTexture> evenColor, unique_ptr<abstractTexture> unevenColor) : even(std::move(evenColor)), uneven(std::move(unevenColor))
	{

	}

	checkerBoard::checkerBoard(vec3 evenColor, vec3 unevenColor) : even(make_unique<solidColor>(evenColor)), uneven(make_unique<solidColor>(unevenColor))
	{

	}

	vec3 checkerBoard::colorValue(float u, float v, vec3& point)
	{
		//This is a pre-defined pattern that works well for checkerboard. 
		float sines = sin(5.f * point.x) * sin(5.f * point.y) * sin(5.f * point.z);
		if (sines < 0)
			return uneven->colorValue(u, v, point);

		return even->colorValue(u, v, point);
	}

};