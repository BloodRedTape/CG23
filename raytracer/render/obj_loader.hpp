#pragma once

#include <string>
#include "utils/expected.hpp"
#include "primitives/mesh.hpp"

struct ObjLoader {
	enum class Error {
		None,
		IO,
		InvalidData
	};

	Expected<Mesh, Error> Load(std::string filename);
};