#pragma once

#include "camera.hpp"
#include "scene.hpp"
#include "math/ray.hpp"
#include "math/vector2.hpp"

enum class RenderMode {
	Color,
	Intersection,
	Distance
};


class ConsoleRenderer {
private:
	Vector2s m_Viewport;
public:
	ConsoleRenderer(Vector2s viewport);

	void Render(const Scene &scene, const Camera &camera, RenderMode mode);

private:

	Ray3f GenRay(Vector2s pixel_coordinate, const Camera &camera);

	std::optional<HitResult> TraceRay(Ray3f ray, const Scene &scene);

	char Miss();

	char ClosestHit(HitResult hit, const Scene &scene);
};