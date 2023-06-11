#include "image_renderer.hpp"
#include "utils/int_iterator.hpp"
#include "utils/random.hpp"
#include <algorithm>
#include <execution>
#include <atomic>
#include <iostream>

Vector3f RandUnitVec3() {
	return Math::Normalize<float>({
		Rand<float>(-1, 1),
		Rand<float>(-1, 1),
		Rand<float>(-1, 1)
	});
}
	
ImageRenderer::ImageRenderer(Vector2s viewport):
	BaseRenderer(viewport)
{}

Image ImageRenderer::Render(const Scene& scene, const Camera& camera, size_t samples, size_t bounces)const{
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

				color += TracePath(ray, scene, bounces);
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

Vector3f ImageRenderer::TracePath(const Ray3f &ray, const Scene& scene, size_t bounces_left)const {
	if(bounces_left == 0)
		return Vector3f();


	std::optional<HitResult> hit = TraceRay(ray, scene);

	if(!hit)
		return scene.SampleSkyColor(ray.Direction());


	MaterialProperties mat = hit->Material;

	Vector3f diffuse_direction = Math::Normalize(hit->Normal + RandUnitVec3());
	Vector3f specular_direction = Math::Normalize(Math::Lerp(Math::Reflect(ray.Direction(), hit->Normal), diffuse_direction, mat.Roughness));

	bool is_spec = Rand<float>(0, 1) >= mat.Metallic;

	Vector3f ray_dir = is_spec ? specular_direction : diffuse_direction;

	Ray3f new_ray(hit->Position + ray_dir * 0.0001f, ray_dir);

	Vector3f incoming_color = TracePath(new_ray, scene, bounces_left - 1);

	Vector3f emmited_light = mat.EmissionColor * mat.EmissionStrength;
	Vector3f surface_color = mat.Color;


	return (is_spec ? incoming_color * Math::Lerp(surface_color, Vector3f(1), mat.Metallic): incoming_color * surface_color) + emmited_light;
}
