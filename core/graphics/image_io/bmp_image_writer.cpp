#include "bmp_image_writer.hpp"
#include "bmp_header.hpp"
#include "math/functions.hpp"
#include <cassert>

ImageWriter::Error BMPImageWriter::Write(const Image& image, std::ostream& outstream)const {
	if(!image.IsValid())
		return Error::InvalidImage;

	BMPHeader header;
    header.filesize = sizeof(BMPHeader) + Math::AlignUp<int>(image.Width() * Channels, RowAlignment) * image.Height();
    header.width = image.Width();
    header.depth = image.Height();

    outstream.write((const char*)&header, sizeof(header));

    for (int y = image.Height() - 1; y >= 0; y--) {
        for (int x = 0; x < image.Width(); x++) {
            //write them in a reverse because bmp image uses inverse byte ordering
            outstream.write((const char *)& image.Get(x, y).B, 1);
            outstream.write((const char *)& image.Get(x, y).G, 1);
            outstream.write((const char *)& image.Get(x, y).R, 1);
        }

        static const u32 NullBytes = 0;
        const int row_size = image.Width() * Channels;
        const int null_bytes_count = Math::AlignUp<int>(row_size, RowAlignment) - row_size;

        assert(null_bytes_count <= sizeof(NullBytes));
        outstream.write((const char *)&NullBytes, null_bytes_count);
    }

	return Error::None;
}

std::string BMPImageWriter::FormatExtension()const {
	return ".bmp";
}