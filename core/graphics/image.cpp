#include "image.hpp"
#include <cstring>
#include <cassert>
#include <filesystem>
#include <fstream>
#include "graphics\image_io/image_reader_factory.hpp"
#include "graphics\image_io/image_writer_factory.hpp"

Image::Image(size_t width, size_t height):
	m_Width(width),
	m_Height(height)
{
	const size_t mem_size = sizeof(Color) * width * height;

	m_Data = (Color*)std::malloc(mem_size);

	if (!m_Data)
		return;

	//set all pixels to white, kinda ultra-fast hack
	std::memset(m_Data, -1, mem_size);
}
Image::Image(Image&&other)noexcept {
	*this = std::move(other);
}

Image& Image::operator=(Image&&image)noexcept {
	Clear();

	std::swap(m_Data, image.m_Data);
	std::swap(m_Width, image.m_Width);
	std::swap(m_Height, image.m_Height);

	return *this;
}

Image::~Image() {
	Clear();
}

const Color& Image::Get(size_t x, size_t y)const {
	assert(x < m_Width, y < m_Height);

	return m_Data[y * m_Width + x];
}

void Image::Clear() {
	m_Width = 0;
	m_Height = 0;
	std::free(m_Data);
	m_Data = nullptr;
}

bool Image::SaveImageTo(const std::string& filename)const{
	const ImageWriter *writer = ImageWriterFactory::FindImageWriterFor(std::filesystem::path(filename).extension().string());

	if(!writer)
		return false;

	std::fstream file(filename, std::ios::binary | std::ios::out);

	if(!file.is_open())
		return false;

	return writer->Write(*this, file) == ImageWriter::Error::None;
}

std::optional<Image> Image::ReadImageFrom(const std::string& filename) {
	const ImageReader* reader = ImageReaderFactory::FindImageReaderFor(std::filesystem::path(filename).extension().string());

	if (!reader)
		return {};

	std::fstream file(filename, std::ios::binary | std::ios::in);

	if (!file.is_open())
		return {};

	Expected<Image, ImageReader::Error> image = reader->Read(file);

	if(image.IsError())
		return {};

	return {std::move(image.Value())};
}