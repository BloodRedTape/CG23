#pragma once

#include "core/math/vector3.hpp"

struct Camera {
	Vector3f Position;
	float FOV = 90.f;
};