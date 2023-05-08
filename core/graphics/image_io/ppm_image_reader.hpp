#pragma once

#include "graphics/image_io/image_reader.hpp"

struct PPMImageReader : public ImageReader {
	Expected<Image, Error> Read(std::istream &instream)const override;

	std::string FormatExtension()const override;
};