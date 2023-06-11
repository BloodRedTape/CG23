#pragma once

#include "image_reader.hpp"

struct PNGImageReader : ImageReader {
	Expected<Image, Error> Read(std::istream &instream)const override;

	std::string FormatExtension()const override{return ".png"; }
};