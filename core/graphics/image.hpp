#pragma once

#include <string>
#include "graphics/color.hpp"
#include <optional>

class Image {
private:
	Color *m_Data = nullptr;
	size_t m_Width = 0;
	size_t m_Height = 0;
public:
	Image();

	Image(size_t width, size_t height);

	Image(const Image &) = delete;

	Image(Image &&)noexcept;

	~Image();

	Image &operator=(const Image &) = delete;

	Image &operator=(Image &&)noexcept;

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

	bool IsValid()const {
		return m_Width && m_Height && m_Data;
	}

	void Clear();
};