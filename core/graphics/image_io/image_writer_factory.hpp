#pragma once

#include "image_writer.hpp"
#include <vector>

struct ImageWriterFactory {
	static const ImageWriter *FindImageWriterFor(const std::string &format_extension);

	static std::vector<std::string> GetSupportedFormats();
};