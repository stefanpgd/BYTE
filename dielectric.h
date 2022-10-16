#pragma once
#include "abstractMaterial.h"

namespace Tmpl8 {
    class dielectric :
        public abstractMaterial
    {
    public:
        dielectric(float refractionIndex);
        //Schilick's approximation
        bool scatterRay(const ray& r_in, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay);
        vec3 beer(const float& distance);
        vec3 m_color;
        vec3 m_refractedRay;
        float m_refractionIndex;
    private:
        float Schlick(const float& cosine, const float& refIdx);
        float Fresnel(const float& cosT, const float& n1, const float& n2);
    };

};