#pragma once

#include <string>

struct ArgParse{
	std::string Name;
	std::string &OutValue;
};

template<size_t len>
int Parse(ArgParse(&args)[len], int argc, const char** argv) {

	for (int i = 0; i < argc; i++) {
		std::string arg = argv[i];

		for (int j = 0; j<len; j++) {
			ArgParse& arg_parse = args[j];
			std::string prefix = "--" + arg_parse.Name + '=';

			if (arg.find(prefix) == 0) {
				std::string value = arg.substr(prefix.size(), arg.size() - prefix.size());

				if(!value.size())
					return i;

				arg_parse.OutValue = value;
			}
		}
	}

	return -1;
}
