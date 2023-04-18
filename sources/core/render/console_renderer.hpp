#pragma once

#include "camera.hpp"
#include "scene.hpp"
#include "core/math/ray.hpp"
#include "core/math/vector2.hpp"

class ConsoleRenderer {
private:
	Vector2s m_Viewport;
public:
	ConsoleRenderer(Vector2s viewport);

	void Render(const Scene &scene, const Camera &camera);

private:

	Ray3f GenRay(Vector2s pixel_coordinate, const Camera &camera);

	std::optional<HitResult> TraceRay(Ray3f ray, const Scene &scene);

	char Miss();

	char ClosestHit(HitResult hit, const Scene &scene);
};