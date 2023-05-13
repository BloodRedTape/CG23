#pragma once

#include <assert.h>
#include <cstdlib>

template<typename T>
T Rand(T min, T max) {
	assert(false);
	return T();
}

template<>
float Rand<float>(float min, float max) {
	return min + (rand() / float(RAND_MAX)) * (max - min);
}
