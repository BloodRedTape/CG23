#include "obj_loader.hpp"
#include "math/transform.hpp"
#include <fstream>
#include <sstream>

Expected<Mesh, ObjLoader::Error> ObjLoader::Load(std::string filename, const Vector3f position, const Vector3f rotation, const Vector3f scale) {
	std::fstream file(filename, std::ios::in);

	if(!file.is_open())
		return Error::IO;

	std::vector<Vector3f> vertices;
	std::vector<Vector3u> faces;

	Matrix4f transformation = Math::Translate(position) * Math::Rotate<float>(Math::Rad(rotation)) * Math::Scale(scale);

	while (file) {
		std::string line;
		std::getline(file, line);

		if(!line.size())
			continue;

		std::stringstream line_stream(line);

		std::string line_type;
		line_stream >> line_type;

		if (line_type == "v") {
			Vector3f vertex;
			line_stream >> vertex.x >> vertex.y >> vertex.z;

			vertex = transformation * Vector4f(vertex);

			vertices.push_back(vertex);
		}
		if (line_type == "f") {

			std::string temp;
			Vector3s face;

			for(int i = 0; i<3; i++){
				line_stream >> face[i];

				std::getline(line_stream, temp, ' ');
			}

			faces.push_back(face);
		}
	}

	std::vector<Triangle> triangles;

	for (const Vector3u &face : faces){
		triangles.push_back(
			Triangle(
				{ vertices[face.x - 1], vertices[face.y - 1], vertices[face.z - 1] }
			)
		);
	}

	return Mesh(std::move(triangles));
}
