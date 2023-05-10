#pragma once

#include "math/vector3.hpp"

struct Camera {
	Vector3f Position;
	Vector3f Rotation;
	float FOV = 90.f;

	Vector3f Forward()const;

	Vector3f Up()const;

	Vector3f Right()const;
};