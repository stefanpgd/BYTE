#pragma once
#include "precomp.h"
#include "RayTracingUtilities.h"
#include "ray.h"
#include "abstractHittable.h"

namespace Tmpl8 {


	class abstractLight
	{
	public:
		virtual vec3 getPosition() = 0;
		virtual vec3 Attenuation(const float& rSquared, hitRecordStruct& hitRecord, const vec3& angleIncidence) = 0;
	};

}