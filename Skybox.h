#pragma once
#include "abstractTexture.h"

namespace Tmpl8
{
	using std::unique_ptr;
	using std::make_unique;
	class Skybox
	{
	public:
		Skybox(const vec3& color);
		Skybox(unique_ptr<abstractTexture> color);
		vec3 getColor(float& u, float& v, vec3 point);
		unique_ptr<abstractTexture> albedoValue;
	};

	static void GetSphereUV(float& u, float& v, const vec3& point);
}