#pragma once
#include "abstractMaterial.h"

namespace Tmpl8 {
	class metal : public abstractMaterial
	{
	public:
		metal(const vec3& color, float passFuzz);

		bool scatterRay(const ray& r_in, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay);

		vec3 m_color;
		vec3 m_reflectedRay;
		vec3 m_scatteredRay;
		float fuzz;

	};
};
