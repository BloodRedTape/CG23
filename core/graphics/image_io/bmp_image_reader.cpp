#include "bmp_image_reader.hpp"
#include "bmp_header.hpp"
#include "math/functions.hpp"
#include <cassert>

Expected<Image, ImageReader::Error> BMPImageReader::Read(std::istream& instream)const {
	
	BMPHeader header;
    instream.read((char*)&header, sizeof(header));

    if(!header.depth || !header.width || !header.filesize || instream.eof())
        return Error::InvalidData;

    Image image(header.width, header.depth);

    for (int y = image.Height() - 1; y >= 0; y--) {
        for (int x = 0; x < image.Width(); x++) {
            //read them in a reverse because bmp image uses inverse byte ordering

            Color &color = image.Get(x, y);
            instream.read((char*)&color.B, 1);
            instream.read((char*)&color.G, 1);
            instream.read((char*)&color.R, 1);
            color.A = Color::MaxChannelValue;

            if(instream.eof())
                return Error::IO;
        }

        u32 TempBuffer = 0;
        const int row_size = image.Width() * Channels;
        const int null_bytes_count = Math::AlignUp<int>(row_size, RowAlignment) - row_size;

        assert(null_bytes_count <= sizeof(TempBuffer));
        instream.read((char *)&TempBuffer, null_bytes_count);
    }

    return {std::move(image)};
}

std::string BMPImageReader::FormatExtension()const {
	return ".bmp";
}