#include "precomp.h"
#include "ListOfHittables.h"



namespace Tmpl8 {


	ListOfHittables::ListOfHittables()
	{

	}

	ListOfHittables::ListOfHittables(abstractHittable* object)
	{
		AddToList(object);
	}

	void ListOfHittables::AddToList(abstractHittable* object)
	{
		//Push_Back is what you use to add something to the std vector. 
		objects.push_back(object);
	}

	void ListOfHittables::clear()
	{
		objects.clear();
	}

	bool ListOfHittables::hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const
	{
		hitRecordStruct tempHitRecord;
		bool intersection = false;
		float closestSoFar = biggestT;

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->hit(r, tempHitRecord, smallestT, closestSoFar))
			{
				intersection = true;
				closestSoFar = tempHitRecord.t;
				hitrecord = tempHitRecord;
			}
		}

		return intersection;
	}

	void ListOfHittables::boundingBox(aabb& box) const
	{
		vec3 zeroValue = vec3(0.f);
		aabb zeroBox(zeroValue, zeroValue);
		bool firstBox = true;

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i]->boundingBox(zeroBox);
			if (firstBox)
			{
				box = zeroBox;
			}
			else
			{
				box = boxBox(box, zeroBox);
			}
			firstBox = false;

		}
	}
};