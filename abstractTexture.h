#pragma once
#include "precomp.h"

namespace Tmpl8 {
	//Texture implementation taken from the book Ray Tracing: The Next Week, by Peter Shirley. 
	class abstractTexture {
	public:
		virtual vec3 colorValue(float u, float v, vec3& point) = 0;
		virtual ~abstractTexture() {};
	};
};