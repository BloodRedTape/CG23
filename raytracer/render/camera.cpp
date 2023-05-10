#include "camera.hpp"
#include "math/transform.hpp"

Vector3f Camera::Forward()const {
	return Math::Normalize((Math::Rotate<float>(Math::Rad(Rotation)) * Vector4f(Vector3f::Forward())).XYZ());
}

Vector3f Camera::Up()const{
	return Math::Normalize((Math::Rotate<float>(Math::Rad(Rotation)) * Vector4f(Vector3f::Up())).XYZ());
}

Vector3f Camera::Right()const {
	return Math::Normalize((Math::Rotate<float>(Math::Rad(Rotation)) * Vector4f(Vector3f::Right())).XYZ());
}