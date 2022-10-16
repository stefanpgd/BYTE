#pragma once
#include "abstractMaterial.h"
#include "abstractTexture.h"

namespace Tmpl8 {
    using std::unique_ptr;
    using std::make_unique;
    class checkerBoard :
        public abstractTexture
    {
    public:
        checkerBoard(unique_ptr<abstractTexture> evenColor, unique_ptr<abstractTexture> unevenColor);
        checkerBoard(vec3 evenColor, vec3 unevenColor);
        vec3 colorValue(float u, float v, vec3& point);

        unique_ptr<abstractTexture> even;
        unique_ptr<abstractTexture> uneven;
    };

}