#include "ppm_image_writer.hpp"
#include <fstream>

ImageWriter::Error PPMImageWriter::Write(const Image& image, std::ostream &file)const {
	if(!image.IsValid())
		return Error::InvalidImage;

	if(file.flags() == std::ios::binary)
		return Error::IO;

	constexpr char Newline = '\n';
	constexpr char Space = ' ';
	constexpr char Tab = '\t';

	file << "P3" << Newline;

	file << image.Width() << Space << image.Height() << Newline;
	constexpr auto MaxChannelValue = 255;
	file << MaxChannelValue << Newline;

	for(size_t y = 0; y<image.Height(); y++){
		for (size_t x = 0; ; x++) {
			Color color = image.Get(x, y);
			file << (int)color.R << Space << (int)color.G << Space << (int)color.B;

			if(x == image.Width() - 1)
				break;

			file << Tab;
		}

		file << Newline;
	}

	return Error::None;
}

std::string PPMImageWriter::FormatExtension()const {
	return ".ppm";
}
