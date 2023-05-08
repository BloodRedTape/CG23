#pragma once

#include "graphics/image_writer.hpp"

struct PPMImageWriter: ImageWriter{
	ImageWriter::Error Write(const Image &image, std::ostream &outstream)const override;

	std::string FormatExtension()const override;
};