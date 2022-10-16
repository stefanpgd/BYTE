#pragma once
#include "precomp.h"
#include "RayTracingUtilities.h"
#include "ray.h"

namespace Tmpl8 {
	struct hitRecordStruct;

	class abstractMaterial
	{
	public:
		virtual bool scatterRay(const ray& r_in, hitRecordStruct& hitrecord, vec3& attenuation, ray& scatteredRay) = 0;
		virtual bool diffuseCheck()
		{
			return false;
		}

		virtual vec3 emission()
		{
			return vec3(0);
		}
	};
}