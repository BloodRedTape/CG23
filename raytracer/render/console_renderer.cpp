#include "console_renderer.hpp"
#include "math/functions.hpp" 
#include "math/vector2.hpp"
#include <algorithm>

ConsoleRenderer::ConsoleRenderer(Vector2s viewport):
	m_Viewport(viewport)
{}

void ConsoleRenderer::Render(const Scene& scene, const Camera& camera, RenderMode mode) {
	puts("Final Image: ");

	for (int y = m_Viewport.y; y >= 0; y--) {
		for (int x = 0; x < m_Viewport.x; x++) {
			Ray3f ray = GenRay({x, y}, camera);

			std::optional<HitResult> result = TraceRay(ray, scene);

			switch (mode) {
			case RenderMode::Color:
				putchar(result.has_value() ? ClosestHit(*result, scene) : Miss());
				break;
			case RenderMode::Intersection:
				putchar(result.has_value() ? '#' : ' ');
				break;
			case RenderMode::Distance:
				result.has_value() ? printf("%2.1f ", result->Distance) : printf("null ");
				break;
			}
		}

		putchar('\n');
	}
}

Ray3f ConsoleRenderer::GenRay(Vector2s pixel_coordinate, const Camera& camera) {
	const float aspect = m_Viewport.x / m_Viewport.y;

	float h_fov = camera.FOV / 2.f;
	float projection_plane_distance = -Math::Cos(h_fov);
	float projection_plane_width = -Math::Sin(h_fov) * 2;
	assert(projection_plane_distance > 0 && projection_plane_width > 0);

	Vector2f projection_plane_size = {projection_plane_width, projection_plane_width / aspect};

	Vector2f projection_plane_pixel_size = projection_plane_size / Vector2f(m_Viewport);

	assert(Math::IsNearlyEqual(projection_plane_pixel_size.x, projection_plane_pixel_size.y));

	Vector2f centered_coordinates = pixel_coordinate - m_Viewport / 2;

	Vector2f projection_plane_ray_intersect = centered_coordinates * projection_plane_pixel_size + projection_plane_pixel_size / 2.f;

	Vector3f direction = 
		  Vector3f::Forward() * projection_plane_distance
		+ Vector3f::Right() * projection_plane_ray_intersect.x 
		+ Vector3f::Up() * projection_plane_ray_intersect.y;

	Vector3f origin = camera.Position;

	return Ray3f(origin, Math::Normalize(direction));
}

std::optional<HitResult> ConsoleRenderer::TraceRay(Ray3f ray, const Scene &scene) {
	std::optional<HitResult> closest_hit;

	for (const HittableRef& hittable : scene.Objects) {
		std::optional<HitResult> hit = hittable->Hit(ray, 0.f, FLT_MAX);


		if(hit.has_value()){

			if(closest_hit.has_value()){
				if(hit->Distance < closest_hit->Distance)
					closest_hit = hit;
			}else{
				closest_hit = hit;
			}
		}
	}

	return closest_hit;
}

char ConsoleRenderer::Miss() {
	return ' ';
}

char ConsoleRenderer::ClosestHit(HitResult hit, const Scene &scene) {
	Vector3f light_to_object_direction = scene.PointLight.Position - hit.Position;

	float diffuse = std::max(Math::Dot(hit.Normal, light_to_object_direction), 0.f);

	const char colors[] = ".*#0@";
	int colors_count = lengthof(colors) - 1;

	int index = Math::Clamp<int>(diffuse * 4, 0, colors_count - 1);

	return colors[index];
}
