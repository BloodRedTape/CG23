#pragma once

#include <optional>
#include "core/math/vector3.hpp"
#include "core/math/ray.hpp"

struct HitResult {
	Vector3f Position;
};

struct Hittable{
	virtual std::optional<HitResult> Hit(const Ray3f &ray) = 0;
};