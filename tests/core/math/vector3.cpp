#include "core/math/vector3.hpp"
#include "core/math/functions.hpp"
#include "gtest/gtest.h"


TEST(Math, VectorOperations) {
	Vector3f vec1(1, -2, 9);
	Vector3f vec2(2, 1, -3);

	ASSERT_EQ(Math::Dot(vec1, vec2), -27.f);
	ASSERT_EQ(Math::Cross(vec1, vec2), Vector3f(-3, 21, 5));

	Vector3f vec3(0, 9, 0);
	ASSERT_EQ(vec3.Length(), 9);
	ASSERT_EQ(Math::Normalize(vec3), Vector3f(0, 1, 0));

}