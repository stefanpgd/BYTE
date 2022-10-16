#include "precomp.h"
#include "imageTexture.h"
#include "RayTracingUtilities.h"

namespace Tmpl8
{
	imageTexture::imageTexture(const char* filename)
	{
		image = new Sprite(new Surface(filename), 1);
		spriteWidth = image->GetWidth();
		spriteHeight = image->GetHeight();
		imageData = image->GetBuffer(); //Gets the start of the large array of the image data. 
	}

	vec3 imageTexture::colorValue(float u, float v, vec3& )
	{
		if (imageData == nullptr) return vec3(1.f, 1.f, 0.f);

		u = floatClamp(u, 0.f, 1.f);
		v = 1.f - floatClamp(v, 0.f, 1.f);

		int x = static_cast<int>(u * spriteWidth);
		int y = static_cast<int>(v * spriteHeight);

		if (x >= spriteWidth)
			x = spriteWidth - 1;
		if (y >= spriteHeight)
			y = spriteHeight - 1;

		float scale = 1.f / 255.f;
		Pixel color = imageData[x + y * spriteWidth];
		int red = ((color & RedMask) >> 16);
		int green = ((color & GreenMask) >> 8);
		int blue = (color & BlueMask);
		return vec3(scale * red, scale * green, scale * blue);
	}

}