#pragma once
#include "abstractTexture.h"
namespace Tmpl8 {

    class imageTexture :
        public abstractTexture
    {
    public:
        imageTexture(const char* filename);
        vec3 colorValue(float u, float v, vec3& point);

    private:
        Sprite* image = nullptr;
        int spriteWidth;
        int spriteHeight;
        Pixel* imageData;
    };

}