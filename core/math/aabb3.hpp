#pragma once

#include <utility>
#include "math/vector3.hpp"
#include "math/ray.hpp"

template <typename Type>
struct AABB3 {
	Vector3<Type> Min;
	Vector3<Type> Max;

	AABB3(const Vector3<Type> &min, const Vector3<Type> &max):
		Min(min),
		Max(max)
	{}

	bool Inside(const Vector3<Type>& point)const{
		return Min.x <= point.x && point.x <= Max.x
			&& Min.y <= point.y && point.y <= Max.y
			&& Min.z <= point.z && point.z <= Max.z;
	}

	bool Intersects(const AABB3<Type> &other)const{
		return Min.x <= other.Max.x && Max.x >= other.Min.x
			&& Min.y <= other.Max.y && Max.y >= other.Min.y
			&& Min.z <= other.Max.z && Max.z >= other.Min.z;
	}

	bool Inside(const AABB3<Type>& other)const {
		return Min.x <= other.Min.x
			&& Min.y <= other.Min.y
			&& Min.z <= other.Min.z

			&& Max.x >= other.Max.x
			&& Max.y >= other.Max.y
			&& Max.z >= other.Max.z;
	}

	bool Intersects(const Ray<Vector3<Type>, Type>& ray, float, float)const {
		auto tMin = (Min - ray.Origin()) / ray.Direction();
		auto tMax = (Max - ray.Origin()) / ray.Direction();
		auto t1 = std::min(tMin, tMax);
		auto t2 = std::max(tMin, tMax);
		float tNear = std::max(std::max(t1.x, t1.y), t1.z);
		float tFar = std::min(std::min(t2.x, t2.y), t2.z);
		return tNear < tFar;
	}

	AABB3<Type> CutHalfBy(size_t dimention)const{
		auto size = Size();
		auto position = Position();

		size[dimention] /= (Type)2;

		return {position, position + size};
	}

	Vector3<Type> Position()const {
		return Min;
	}

	Vector3<Type> Size()const {
		return Max - Min;
	}

	Vector3<Type> Center()const {
		return Min + Size()/Type(2);
	}

	AABB3<Type> &operator+=(const AABB3<Type> &other){
		Min = std::min(Min, other.Min);
		Max = std::max(Max, other.Max);
		return *this;
	}
};

using AABB3s = AABB3<s32>;
using AABB3u = AABB3<u32>;
using AABB3f = AABB3<float>;
using AABB3d = AABB3<double>;
