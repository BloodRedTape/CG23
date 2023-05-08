#include "image_writer_factory.hpp"
#include "ppm_image_writer.hpp"
#include "bmp_image_writer.hpp"

static std::unique_ptr<ImageWriter> s_Writers[]{
	std::make_unique<PPMImageWriter>(),
	std::make_unique<BMPImageWriter>()
};

const ImageWriter* ImageWriterFactory::FindImageWriterFor(const std::string& format_extension) {

	for (const std::unique_ptr<ImageWriter>& writer : s_Writers) {
		if(writer->FormatExtension() == format_extension)
			return writer.get();
	}

	return nullptr;
}

std::vector<std::string> ImageWriterFactory::GetSupportedFormats() {
	std::vector<std::string> result;

	for (const std::unique_ptr<ImageWriter>& writer : s_Writers) 
		result.push_back(writer->FormatExtension());

	return result;
}