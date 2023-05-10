#pragma once

#include <string>
#include "utils/expected.hpp"
#include "primitives/mesh.hpp"
#include "math/matrix4.hpp"

struct ObjLoader {
	enum class Error {
		None,
		IO,
		InvalidData
	};

	Expected<Mesh, Error> Load(std::string filename, const Vector3f position = {}, const Vector3f rotation = {}, const Vector3f scale = {1.f, 1.f, 1.f});
};