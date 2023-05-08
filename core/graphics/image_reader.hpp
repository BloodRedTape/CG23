#pragma once

#include <istream>
#include <string>
#include "graphics/image.hpp"
#include "utils/expected.hpp"

struct ImageReader {
	enum class Error{
		IO
	};

	virtual Expected<Image, Error> Read(std::istream &instream)const = 0;

	virtual std::string FormatExtension()const = 0;
};