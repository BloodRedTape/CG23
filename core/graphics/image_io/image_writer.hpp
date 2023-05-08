#pragma once

#include <ostream>
#include <string>
#include "graphics/image.hpp"

struct ImageWriter {
	enum class Error{
		None,
		IO,
		InvalidImage
	};

	virtual Error Write(const Image &image, std::ostream &outstream)const = 0;

	virtual std::string FormatExtension()const = 0;
};