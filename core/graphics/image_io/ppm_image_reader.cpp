#include "ppm_image_reader.hpp"
#include <iostream>

static int MapRange(int value, int src_max, int dst_max) {
	return (int)(((float)value / src_max) * dst_max);
}

Expected<Image, ImageReader::Error> PPMImageReader::Read(std::istream& instream)const {
	std::string magic_word;
	instream >> magic_word;

	if(magic_word != "P3")
		return ImageReader::Error::InvalidData;

	int width = 0, height = 0, max_channel = 0;

	instream >> width >> height >> max_channel;

	if(!width || !height || !max_channel || max_channel > Color::MaxChannelValue || !instream)
		return ImageReader::Error::InvalidData;

	Image image(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if(instream.eof())
				return ImageReader::Error::InvalidData;

			int r, g, b;

			instream >> r >> g >> b;

			//std::cout << r << ' ' << g  << ' ' << b << '\t';


			Color &color = image.Get(x, y);

			color.R = MapRange(r, max_channel, Color::MaxChannelValue);
			color.G = MapRange(g, max_channel, Color::MaxChannelValue);
			color.B = MapRange(b, max_channel, Color::MaxChannelValue);
			color.A = Color::MaxChannelValue;
		}
		//std::cout << '\n';
	}

	return {std::move(image)};
}

std::string PPMImageReader::FormatExtension()const {
	return ".ppm";
}