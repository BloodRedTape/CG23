#pragma once 

#include "core/math/functions.hpp"
#include "core/math/vector3.hpp"
#include "core/math/hittable.hpp"


class Plane: public Hittable {
private:
	Vector3f m_Origin;
	Vector3f m_Normal;
public:
	Plane(Vector3f origin, Vector3f normal) :
		m_Origin(origin),
		m_Normal(normal)
	{}

	std::optional<HitResult> Hit(const Ray3f& ray)const override {
        using namespace Math;

        float dot = Dot(m_Normal, ray.Direction());

        if (Abs(dot) < Epsilon<float>() ) 
            return {};

        float t = Dot(m_Normal, m_Origin - ray.Origin()) / dot;
        if (t < 0.f) 
            return {};

        return {{ ray.At(t)}};
	}

};