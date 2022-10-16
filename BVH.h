#pragma once
#include "abstractHittable.h"
#include "RayTracingUtilities.h" 

namespace Tmpl8 {
    constexpr int bins = 8;
    using std::unique_ptr;
    class aabb;
    class BVH :
        public abstractHittable
    {
    public:
        BVH(ListOfHittables& hittables);
        BVH(std::vector<abstractHittable*> objects, size_t min, size_t max);

        bool hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const;
        void boundingBox(aabb& box) const;
        abstractHittable* left;
        abstractHittable* right;
        aabb BVHBox;
        vec3 m_childLeft;
        vec3 m_childRight;
        vec3 m_BVHParent;
        int m_axis = 0;
        bool m_split = true;

    };

    inline bool boxCompare(abstractHittable* a, abstractHittable* b, int axis)
    {
        aabb boxA;
        aabb boxB;

        a->boundingBox(boxA);
        b->boundingBox(boxB);
        return boxA.m_minimum[axis] < boxB.m_minimum[axis];
    }

    bool boxXCompare(abstractHittable* a, abstractHittable* b);

    bool boxYCompare(abstractHittable* a, abstractHittable* b);

    bool boxZCompare(abstractHittable* a, abstractHittable* b);

};
