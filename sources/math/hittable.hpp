#pragma once

#include <optional>
#include "math/vector3.hpp"
#include "math/ray.hpp"

struct HitResult {
	Vector3f Position;
	Vector3f Normal;
	float Distance;
};

struct Hittable{
	virtual std::optional<HitResult> Hit(const Ray3f &ray, float t_min, float t_max)const = 0;
};