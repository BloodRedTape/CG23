#pragma once

#include "core/types.hpp"

struct Color {
	u8 R = 255;
	u8 G = 255;
	u8 B = 255;
	u8 A = 255;

	Color() = default;

	Color(u8 red, u8 green, u8 blue, u8 alpha):
		R(red),
		G(green),
		B(blue),
		A(alpha)
	{}


	static const Color Green;
	static const Color Red;
	static const Color Blue;
	static const Color Black;
	static const Color While;
};