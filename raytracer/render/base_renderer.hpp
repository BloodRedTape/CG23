#pragma once

#include "camera.hpp"
#include "scene.hpp"
#include "math/ray.hpp"
#include "math/vector2.hpp"

class BaseRenderer {
protected:
	Vector2s m_Viewport;
public:
	BaseRenderer(Vector2s viewport);

	Ray3f GenRay(Vector2s pixel_coordinate, const Camera &camera)const;

	std::optional<HitResult> TraceRay(Ray3f ray, const Scene &scene)const;

};