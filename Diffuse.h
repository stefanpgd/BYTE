#pragma once
#include "abstractMaterial.h"
#include "abstractTexture.h"

namespace Tmpl8 {
	using std::unique_ptr;
	using std::make_unique;
	class Diffuse : public abstractMaterial
	{
	public:
		Diffuse(const vec3& color);
		Diffuse(unique_ptr<abstractTexture> color);
		bool scatterRay(const ray& r_in, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay);
		bool diffuseCheck();
		vec3 m_color;
		vec3 m_scatterDirection;
		vec3 m_scatteredRay;
		unique_ptr<abstractTexture> albedoValue;
	};
};