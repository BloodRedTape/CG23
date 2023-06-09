#include "image_renderer.hpp"
#include "utils/int_iterator.hpp"
#include "utils/random.hpp"
#include <algorithm>
#include <execution>
#include <atomic>
#include <iostream>
	
ImageRenderer::ImageRenderer(Vector2s viewport):
	BaseRenderer(viewport)
{}

Image ImageRenderer::Render(const Scene& scene, const Camera& camera, DebugRenderMode mode, size_t samples)const{
	Image image(m_Viewport.x, m_Viewport.y);

	std::atomic<int> progress;
	const int pixels = m_Viewport.x * m_Viewport.y;

	std::for_each(std::execution::par, IntIterator<int>(0), IntIterator<int>(m_Viewport.y), [&](int y) {
		for (int x = 0; x < m_Viewport.x; x++) {
			Vector3f color;

			for(size_t i = 0; i<samples; i++){
				Vector2f uv(
					(x+Rand<float>(-0.5, 0.5)) / m_Viewport.x,
					(y+Rand<float>(-0.5, 0.5)) / m_Viewport.y
				);

				Ray3f ray = GenRay(uv, camera);

				std::optional<HitResult> result = TraceRay(ray, scene);
				color += (Vector3f)(result.has_value() ? ClosestHit(*result, scene, mode) : Miss(scene));
			}

			//flip vertically because image has inverted coordinates
			image.Get(x, m_Viewport.y - y - 1) = color / (float)samples;

			int done = progress++;

			if(done % (pixels / 100) == 0)
				std::cout << done / (float)pixels * 100.f << "%\n";
		}
	});

	return image;
}

Color ImageRenderer::Miss(const Scene &scene)const{
	return scene.Sky;
}

Color ImageRenderer::ClosestHit(HitResult hit, const Scene& scene, DebugRenderMode mode)const{
	using namespace Math;
	
	switch (mode) {
	case DebugRenderMode::Color:
	{
		return AccumulateDiffuse(hit, scene) * AccumulateShadow(hit, scene);
	}
	case DebugRenderMode::Normal:
		return (hit.Normal + 1.f) * 0.5f;
	case DebugRenderMode::Depth:
		return Vector3f(hit.Distance);
	}
}
Vector3f ImageRenderer::AccumulateDiffuse(HitResult hit, const Scene& scene)const{
	Vector3f diffuse = 0.f;

	for(const Light &light: scene.PointLights){
		Vector3f light_to_object_direction = Math::Normalize(light.Position - hit.Position);

		diffuse += std::max(Math::Dot(hit.Normal, light_to_object_direction), 0.f) * light.Color;
	}

	return diffuse;
}

float ImageRenderer::AccumulateShadow(HitResult hit, const Scene& scene)const {
	float shadow = 1.f;

	for(const Light &light: scene.PointLights){
		Vector3f light_to_object_direction = Math::Normalize(light.Position - hit.Position);

		Vector3f shadow_bias = hit.Normal * 0.001f;
		Ray3f to_light(hit.Position + shadow_bias, light_to_object_direction);
		shadow *= TraceRay(to_light, scene).has_value() ? 0.5f : 1.f;
	}

	return shadow;
}