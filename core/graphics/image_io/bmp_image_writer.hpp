#pragma once

#include "graphics/image_io/image_writer.hpp"

struct BMPImageWriter : ImageWriter {
	Error Write(const Image& image, std::ostream& outstream)const override;

	std::string FormatExtension()const override;
};