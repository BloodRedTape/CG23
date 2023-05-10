#pragma once


#include "math/vector3.hpp"
#include "math/functions.hpp"
#include "primitives/hittable.hpp"

class Triangle: public Hittable{
	Vector3f m_Vertices[3];
public:
	Triangle(const Vector3f (&vertices)[3]):
		m_Vertices{vertices[0], vertices[1], vertices[2]}
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
        using namespace Math;
        auto v0 = m_Vertices[0];
        auto v1 = m_Vertices[1];
        auto v2 = m_Vertices[2];

        auto dir = ray.Direction();
        auto orig = ray.Origin();


        Vector3f normal = Cross(m_Vertices[1] - m_Vertices[0], m_Vertices[2] - m_Vertices[0]);
    
        float NdotRayDirection = Dot(normal, dir);

        if (Abs(NdotRayDirection) < Epsilon<float>()) 
            return {};

        // compute d parameter using equation 2
        float d = -Dot(normal, v0);
    
        float t = -(Dot(normal,orig) + d) / NdotRayDirection;
    
        // check if the triangle is out of the bounds
        if (t < t_min || t > t_max) 
            return {}; // the triangle is behind
 
        // compute the intersection point using equation 1
        Vector3f P = ray.At(t);
 
        // Step 2: inside-outside test
        Vector3f C; // vector perpendicular to triangle's plane
 
        // edge 0
        Vector3f edge0 = v1 - v0;
        Vector3f vp0 = P - v0;
        C = Cross(edge0, vp0);
        if (Dot(normal, C) < 0) 
            return {}; // P is on the right side
 
        // edge 1
        Vector3f edge1 = v2 - v1;
        Vector3f vp1 = P - v1;
        C = Cross(edge1, vp1);
        if (Dot(normal, C) < 0)
            return {}; // P is on the right side
 
        // edge 2
        Vector3f edge2 = v0 - v2;
        Vector3f vp2 = P - v2;
        C = Cross(edge2, vp2);
        if (Dot(normal, C) < 0)
            return {}; // P is on the right side;

        HitResult result;
        result.Position = P;
        result.Normal = normal;
        return { result }; // this ray hits the triangle
	}

};