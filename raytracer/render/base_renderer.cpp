#include "base_renderer.hpp"

BaseRenderer::BaseRenderer(Vector2s viewport):
	m_Viewport(viewport)
{}

Ray3f BaseRenderer::GenRay(Vector2f uv, const Camera& camera)const {
	const float aspect = m_Viewport.x / m_Viewport.y;

	float h_fov = camera.FOV / 2.f;
	float projection_plane_distance = -Math::Cos(h_fov);
	float projection_plane_width = -Math::Sin(h_fov) * 2;
	assert(projection_plane_distance > 0 && projection_plane_width > 0);

	Vector2f projection_plane_size = {projection_plane_width, projection_plane_width / aspect};

	Vector2f projection_plane_pixel_size = projection_plane_size / Vector2f(m_Viewport);

	assert(Math::IsNearlyEqual(projection_plane_pixel_size.x, projection_plane_pixel_size.y));

	Vector2f centered_coordinates = uv - Vector2f(0.5f);

	Vector2f projection_plane_ray_intersect = centered_coordinates + projection_plane_pixel_size / 2.f;

	Vector3f direction = 
		  camera.Forward() * projection_plane_distance
		+ camera.Right() * projection_plane_ray_intersect.x 
		+ camera.Up() * projection_plane_ray_intersect.y;

	Vector3f origin = camera.Position;

	return Ray3f(origin, Math::Normalize(direction));
}

std::optional<HitResult> BaseRenderer::TraceRay(Ray3f ray, const Scene &scene)const {
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