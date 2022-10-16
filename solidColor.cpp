#include "precomp.h"
#include "solidColor.h"

namespace Tmpl8 {
	solidColor::solidColor(vec3 color)
	{
		m_color = color;
	}

	solidColor::solidColor(float red, float green, float blue)
	{
		m_color = vec3(red, green, blue);
	}

	vec3 solidColor::colorValue(float, float, vec3& )
	{
		//You don't need to do anything with UV's here so what does it matter. 
		return m_color;
	}

}
