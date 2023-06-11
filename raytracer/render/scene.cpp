#include "scene.hpp"
#include "math/vector2.hpp"
#include "math/functions.hpp"
#include <cmath>

const Vector2f invAtan = Vector2f(0.1591, 0.3183);
static Vector2f SampleSphericalMap(Vector3f v)
{
    Vector2f uv = Vector2f(atan2(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5f;
    return {uv.x, 1.f - uv.y};
}

Color Scene::SampleSkyColor(Vector3f direction) const
{
	if(!SkySphericalMap.IsValid())
		return SkyFallbackColor;

    Vector2u coords = SampleSphericalMap(direction) * Vector2f(SkySphericalMap.Width(), SkySphericalMap.Height());
    coords.x = Math::Clamp<u32>(coords.x, 0, SkySphericalMap.Width() - 1);
    coords.y = Math::Clamp<u32>(coords.y, 0, SkySphericalMap.Height() - 1);
    return SkySphericalMap.Get(coords.x, coords.y);
}