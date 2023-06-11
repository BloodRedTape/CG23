#include "png_image_reader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct
{
   int      (*read)  (void *user,char *data,int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
   void     (*skip)  (void *user,int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
   int      (*eof)   (void *user);                       // returns nonzero if we are at end of file/data

};

Expected<Image, ImageReader::Error> PNGImageReader::Read(std::istream& instream)const {

	stbi_io_callbacks callbacks{
		[](void *user, char *data, int size)->int {
		    auto &stream = *(std::istream*)user;

			stream.read(data, size);
			return stream.gcount();
        },
		[](void* user, int n) {
		    auto &stream = *(std::istream*)user;
			stream.ignore(n);
        },
		[](void* user)->int {
		    auto &stream = *(std::istream*)user;
			return stream.eof();
        }
	};
	int width, height, comp = 4;
	unsigned char *memory = stbi_load_from_callbacks(&callbacks, &instream, &width, &height, &comp, 4);

	if(!memory)
		return ImageReader::Error::IO;

	Image image(width, height);

	std::memcpy(image.Data(), memory, width * height * comp);

	STBI_FREE(memory);

	return std::move(image);
}
