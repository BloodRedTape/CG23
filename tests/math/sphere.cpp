#include "math/sphere.hpp"
#include "math/functions.hpp"
#include "gtest/gtest.h"


TEST(Math, Sphere) {
	Ray3f ray1(-Vector3f::Forward() * 4.f, Vector3f::Forward());
	Ray3f ray2(-Vector3f::Forward()  * 4.f, Vector3f::Up());

	Sphere sphere({0, 0, 0}, 3.f);

	ASSERT_EQ(sphere.Hit(ray1, 0, FLT_MAX).has_value(), true);
	ASSERT_EQ(sphere.Hit(ray2, 0, FLT_MAX).has_value(), false);
}
