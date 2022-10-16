#include "precomp.h"
#include "abstractHittable.h"
#include "Diffuse.h"
#include "RayTracingUtilities.h"
#include "solidColor.h"

namespace Tmpl8 {

	Diffuse::Diffuse(const vec3& color) : albedoValue(std::move(make_unique<solidColor>(color)))
	{

	}

	Diffuse::Diffuse(unique_ptr<abstractTexture> color) : albedoValue(std::move(color))
	{

	}

	bool Diffuse::diffuseCheck()
	{
		return true;
	}

	bool Diffuse::scatterRay(const ray&, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay)
	{
	
		m_scatterDirection = hitRecord.normal + randomUnitVector();
		//Prevent 0 divisions
		if (m_scatterDirection.nearZero()) m_scatterDirection = hitRecord.normal;

		scatteredRay = ray(hitRecord.point, m_scatterDirection);
		attenuation = albedoValue->colorValue(hitRecord.u, hitRecord.v, hitRecord.point);
		return true;
	}
};