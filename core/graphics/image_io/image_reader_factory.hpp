#pragma once

#include <vector>
#include "graphics/image_io/image_reader.hpp"

struct ImageReaderFactory {
	static const ImageReader *FindImageReaderFor(const std::string &format_extension);

	static std::vector<std::string> GetSupportedFormats();
};