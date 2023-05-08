#pragma once

#include "utils/types.hpp"
#include <limits>

struct Color {
	static constexpr u8 MaxChannelValue = std::numeric_limits<u8>::max();

	u8 R = MaxChannelValue;
	u8 G = MaxChannelValue;
	u8 B = MaxChannelValue;
	u8 A = MaxChannelValue;

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