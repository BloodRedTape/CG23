#include "graphics/image.hpp"
#include <filesystem>
#include <fstream>
#include "graphics/image_io/image_writer_factory.hpp"
#include "graphics/image_io/image_reader_factory.hpp"
#include "utils/args.hpp"
#include "utils/error.hpp"
#include <windows.h>

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& data) {
	if(data.size()){
		for (int i = 0; ; i++) {
			stream << data[i];

			if(i == data.size() - 1)
				break;

			stream << ", ";
		}
	}
	return stream;
}

int main(int argc, const char **argv) {
	std::string input_path;
	std::string target_format;
	std::string output_path;

	if(!IsDebuggerPresent()){
		if (argc <= 1)
			return Error("Can't run convertor without any parameters");

		ArgParse parse_args[] = {
		{
			"input",
			input_path
        },
		{
			"target",
			target_format
        },
		{
			"output",
			output_path
        },
		};

		int arg_parse_fail = Parse(parse_args, argc - 1, argv + 1);

		if (arg_parse_fail != -1)
			return Error("Argument: % has an empty value", parse_args[arg_parse_fail].Name);
	} else {
		input_path = "../test_pic.bmp";
		output_path = "../test_pic2.ppm";
	}

	Error("input: %, target: %, output: %", input_path, target_format, output_path);

	if(!input_path.size())
		return Error("Provide --input argument, else how we can know what to convert lol");

	if(!target_format.size() && !output_path.size())
		return Error("Provide --target or --output argument, else how we can know what format convert to lol");

		
	if(!output_path.size())
		output_path = std::filesystem::path(input_path).replace_extension(target_format).string();

	if(!target_format.size()){
		target_format = std::filesystem::path(output_path).extension().string();
		target_format = target_format.substr(1, target_format.size() - 1);
	}

	target_format = "." + target_format;

	if(target_format.size() && std::filesystem::path(output_path).extension() != target_format)
		return Error("Looks like you haven't decide, whether convert to % or %, please make sure that arguments are coherent", target_format, std::filesystem::path(output_path).extension());
	 
	std::string input_format = std::filesystem::path(input_path).extension().string();

	if(!input_format.size())
		return Error("Looks like your --input=% has invalid format", input_path);

	const ImageReader *reader = ImageReaderFactory::FindImageReaderFor(input_format);
	if(!reader)
		return Error("% input format is not supported, try %", input_format, ImageReaderFactory::GetSupportedFormats());

	std::fstream in_file(input_path, std::ios::binary | std::ios::in);

	if(!in_file.is_open())
		return Error("Can't read file from %", input_path);
	
	Expected<Image, ImageReader::Error> image = reader->Read(in_file);

	if(image.IsError())
		return Error("File reading failed because of IO error");

	const ImageWriter *writer = ImageWriterFactory::FindImageWriterFor(target_format);
	if(!writer)
		return Error("% output format is not supported, try %", target_format, ImageWriterFactory::GetSupportedFormats());

	std::fstream out_file(output_path, std::ios::binary | std::ios::out);

	if(!out_file.is_open())
		return Error("Can't write file to %", output_path);

	ImageWriter::Error result = writer->Write(image.Value(), out_file);

	if(result != ImageWriter::Error::None)
		return Error("Image writing failed");

	std::cout << "Done!\n";
}
