#pragma once

#include <iostream>

template<typename ...ArgsType, typename FirstArgType>
int Error(const char* fmt, FirstArgType arg, ArgsType...args) {
	while (*fmt) {
		if (*fmt == '%') {
			std::cerr << arg;
			return Error(fmt + 1, args...);
		} else {
			std::cerr << *fmt++;
		}
	}
}

inline int Error(const char* fmt) {
	std::cerr << fmt << '\n';

	return EXIT_FAILURE;
}
