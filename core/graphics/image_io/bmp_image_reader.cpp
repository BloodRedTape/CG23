#include "bmp_image_reader.hpp"
#include "bmp_header.hpp"
#include "math/functions.hpp"
#include <iostream>
#include <cassert>

Expected<Image, ImageReader::Error> BMPImageReader::Read(std::istream& instream)const {
	
	BMPHeader header;
    instream.read((char*)&header, sizeof(header));

    if(!header.depth || !header.width || !header.filesize || instream.eof())
        return Error::InvalidData;

    if(header.bits != 24)
        return Error::InvalidData;

    if(header.headersize >= sizeof(BMPHeader))
        //make sure we ignore header bytes if it contains more data than we support
        instream.ignore(header.headersize - sizeof(BMPHeader));
    else
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

        const int row_size = image.Width() * Channels;
        const int null_bytes_count = Math::AlignUp<int>(row_size, RowAlignment) - row_size;

        instream.ignore(null_bytes_count);
    }

    return {std::move(image)};
}

std::string BMPImageReader::FormatExtension()const {
	return ".bmp";
}