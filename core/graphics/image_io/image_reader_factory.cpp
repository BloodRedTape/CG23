#include "image_reader_factory.hpp"
#include "ppm_image_reader.hpp"

static std::unique_ptr<ImageReader> s_Readers[]{
	std::make_unique<PPMImageReader>()
};

const ImageReader* ImageReaderFactory::FindImageReaderFor(const std::string& format_extension) {
	for (const std::unique_ptr<ImageReader>& reader: s_Readers) {
		if(reader->FormatExtension() == format_extension)
			return reader.get();
	}
	return nullptr;
}

std::vector<std::string> ImageReaderFactory::GetSupportedFormats() {
	std::vector<std::string> result;

	for (const std::unique_ptr<ImageReader>& reader: s_Readers) 
		result.push_back(reader->FormatExtension());

	return result;
}