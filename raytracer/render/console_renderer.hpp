#pragma once

#include "render/base_renderer.hpp"

enum class RenderMode {
	Color,
	Intersection,
	Distance
};


class ConsoleRenderer: private BaseRenderer{
public:
	ConsoleRenderer(Vector2s viewport);

	void Render(const Scene &scene, const Camera &camera, RenderMode mode)const;

private:

	char Miss()const;

	char ClosestHit(HitResult hit, const Scene &scene)const;
};