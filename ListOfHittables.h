#pragma once
#include "abstractHittable.h"
#include <memory>
#include <vector>

namespace Tmpl8 {
    //This file is mostly stolen from the Ray Tracing in One Weekend book. I will try to figure out how to do this on my own through this. 
    using std::unique_ptr;
    using std::make_unique;


    class ListOfHittables :
        public abstractHittable
    {

    public:
        ListOfHittables();
        ListOfHittables(abstractHittable* object);

        void AddToList(abstractHittable* object);
        void clear();

        bool hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const;
        void boundingBox(aabb& box) const;
        //This is a vector: a dynamic array. Objects is a dynamic array!!
        std::vector<abstractHittable*> objects;

    };
};
