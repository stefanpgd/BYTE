#pragma once
#include "abstractTexture.h"

namespace Tmpl8 {
    class solidColor :
        public abstractTexture
    {
    public:
        solidColor(vec3 color);
        solidColor(float red, float green, float blue);
        vec3 colorValue(float u, float v, vec3& point);
    private:
        vec3 m_color;
    };
}
