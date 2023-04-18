#pragma once

#include <memory>
#include <vector>
#include "core/math/hittable.hpp"

using HittableRef = std::unique_ptr<Hittable>;

struct Scene {
	std::vector<HittableRef> Objects;
};