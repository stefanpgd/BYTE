#include "precomp.h"
#include "ListOfHittables.h"
#include "ray.h"
#include <algorithm>
#include "BVH.h"

namespace Tmpl8 {
	//https://raytracing.github.io/books/RayTracingTheNextWeek.html

	//Note for information: 
	//Optimal BVH sizes (based on powers of 2): (Every even power of 2 has a Sqrt with a whole outcome. 
	//256 Objects (2^8) sqrt(256) = 16
	//1024 Objects (2^10) sqrt(1024) = 32 
	//4096 Objects (2^12) sqrt(4096) = 64 
	//16384 Objects (2^14) sqrt(16384) = 128 
	//65536 Objects (2^16) sqrt(65536) = 256 
	//262144 Objects (2^18) sqrt(262144) = 512, takes 15 minutes to construct 
	//1048576 Objects (2^20) sqrt(1048576) = 1024

	//Yes I'm writing out powers of 2, what about it?

	BVH::BVH(ListOfHittables& hittables) : BVH((hittables.objects), 0, hittables.objects.size())
	{

	}

	BVH::BVH(std::vector<abstractHittable*> bvhObjects, size_t min, size_t max)
	{

		std::vector<abstractHittable*> objects = bvhObjects;
		//You decide on a random axis here. Improve this later, maybe using SAH. 

		int axis = rand() % 3;

		//Random is faster than going through your axis's in a set order. I don't know why, but I tested both methods. 

		//The comparison here is a function pointer.
		bool (*comparator)(abstractHittable * a, abstractHittable * b) = (axis == 0) ? boxXCompare : (axis == 1) ? boxYCompare : boxZCompare;

		//You use size(t), because std::sort takes in size_t. 
		size_t amountOfObjects = max - min;

		if (amountOfObjects == 1)
		{
			//If you use powers of 2, you will NEVER get here. BVH node construction is logaritmic. 

			//If there is only 1 object, you don't have a left and a right. It's just 1 object. 
			left = right = objects[min];
		}
		else if (amountOfObjects == 2)
		{
			//If there are 2 or less objects, there is no reason to split the branches up anymore. 
			//AABB intersection is slightly more costly than Sphere intersection, so it would be worse. 

			//You stop creating new nodes when you only have 2 objects left within the node.
			if (comparator(objects[min], objects[min + 1]))
			{
				//If m_minimum of object 1 is smaller than m_minimum of object 2, left is object 1. 
				left = objects[min];
				right = objects[min + 1];
			}
			else
			{
				//Reverse here. You always want left to be the smallest one, because you want left to right. 
				left = objects[min + 1];
				right = objects[min];
			}
		}
		else
		{
			//If there are over 2 
			//You pass objects.begin() because it's an iterator. 

			//Sorts from small to big, but for a larger list than the one before. 

			std::sort(objects.begin() + min, objects.begin() + max, comparator);

			//Calculate the entire volume roughly 
			//Incorrect SAH with binning.

			//The amount of bins should not be a sqrt, it should be constant
			//Make sure you construct the whole box again. 
			
			//Instead of zeroValue, you could also make it a const Reference. 
			vec3 zeroValue = vec3(0.f);
			aabb parentBox(zeroValue, zeroValue);
			for (size_t i = min; i < min + amountOfObjects; i++)
			{
				aabb tempBox;
				objects[i]->boundingBox(tempBox);
				parentBox = boxBox(parentBox, tempBox);
			}

			//Calculate parentCost
			//float parentCost = getCost(0.f, 0.f, parentBox.getSurfaceArea(parentBox), amountOfObjects);

			vec3 parentMin = parentBox.m_minimum;
			vec3 parentMax = parentBox.m_maximum;

			float axisSlice = fabs(parentMax[axis] - parentMin[axis]) / bins;

			int objectsPerSlice[bins] = { 0 };
			size_t amountOfBins = bins;

			//Check the amount of objects I have in every bin
			for (size_t i = 0; i < amountOfBins; i++)
			{
				int objectCounter = 0;

				for (size_t j = min; j < min + amountOfObjects; j++)
				{
					aabb tempBox;
					objects[j]->boundingBox(tempBox);
					if (tempBox.m_minimum[axis] >= (parentMin[axis] + axisSlice * i) && tempBox.m_minimum[axis] < (parentMin[axis] + axisSlice * (i + 1)))
					{
						objectCounter++;
					}
				}

				objectsPerSlice[i] = objectCounter;
			}

			size_t mid;
			float lowestCost = FLT_MAX;
			size_t lowestCostIndex = 0;

			size_t objectsOnLeft = 0;

			//Check the cost of every possible split through the bins. 
			for (size_t i = 0; i < amountOfBins; i++)
			{
				objectsOnLeft += objectsPerSlice[i];
				aabb bigBox1;
				aabb bigBox2;

				for (size_t j = min + 1; j < min + objectsOnLeft; j++)
				{
					aabb tempBox;
					if (j == min + 1)
					{
						objects[j - 1]->boundingBox(bigBox1);
					}
					objects[j]->boundingBox(tempBox);
					bigBox1 = boxBox(bigBox1, tempBox);
				}

				for (size_t j = min + objectsOnLeft + 1; j < max; j++)
				{
					aabb tempBox;
					if (j == min + objectsOnLeft + 1)
					{
						objects[j - 1]->boundingBox(bigBox2);
					}
					objects[j]->boundingBox(tempBox);
					bigBox2 = boxBox(bigBox2, tempBox);
				}

				float cost = getCost(bigBox1.getSurfaceArea(bigBox1), static_cast<float>(objectsOnLeft), bigBox2.getSurfaceArea(bigBox2), static_cast<float>(max - objectsOnLeft));
				//Epsilon is to prevent wacky things with near-equal splits.
				if (cost < lowestCost + FLT_EPSILON)
				{

					lowestCost = cost;
					lowestCostIndex = objectsOnLeft;
				}
			}

			mid = static_cast<size_t>(min + lowestCostIndex);
			if (mid == 0 || mid >= max || mid <= min)
				mid = static_cast<size_t>(min + amountOfObjects * 0.5f);


			//Recursively create more nodes by splitting. Ideally you want to always split even numbers, but this is only possible with a select few cases. 
			left = new BVH(objects, min, mid);
			right = new BVH(objects, mid, max);
		}

		aabb leftBox;
		aabb rightBox;

		left->boundingBox(leftBox);
		right->boundingBox(rightBox);

		BVHBox = boxBox(leftBox, rightBox);

	}

	void BVH::boundingBox(aabb& box) const
	{
		box = BVHBox;
	}

	bool BVH::hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const
	{
		if (!BVHBox.hit(r, smallestT, biggestT)) return false;

		bool hitLeft = left->hit(r, hitrecord, smallestT, biggestT);
		bool hitRight = right->hit(r, hitrecord, smallestT, hitLeft ? hitrecord.t : biggestT);
		return hitLeft || hitRight;
	}


	bool boxXCompare(abstractHittable* a, abstractHittable* b)
	{
		return boxCompare(a, b, 0);
	}

	bool boxYCompare(abstractHittable* a, abstractHittable* b)
	{
		return boxCompare(a, b, 1);
	}

	bool boxZCompare(abstractHittable* a, abstractHittable* b)
	{
		return boxCompare(a, b, 2);
	}


};