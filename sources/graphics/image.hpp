#pragma once

#include "graphics/color.hpp"


class Image {
private:
	Color *m_Data = nullptr;
	size_t m_Width = 0;
	size_t m_Height = 0;
public:
	Image(size_t width, size_t height);

	Image(const Image &) = delete;

	~Image();

	Image &operator=(const Image &) = delete;

	Color& Get(size_t x, size_t y) GEN_NON_CONST_GETTER(Get(x, y))

	const Color& Get(size_t x, size_t y)const;

	size_t Width()const {
		return m_Width;
	}

	size_t Height()const {
		return m_Height;
	}

	Color *Data() GEN_NON_CONST_GETTER(Data())

	const Color* Data()const {
		return m_Data;
	}
};