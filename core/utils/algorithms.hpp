#pragma once

#include <initializer_list>

template <typename T, size_t N>
size_t MinIndex(const T (&list)[N]) {
	static_assert(N, "array can't be empty");

	size_t min = 0;

	for(size_t i = 0; i < N; i++)
		if(list[i] < list[min])
			min = i;

	return min;
}

template <typename T, size_t N>
T Min(const T(&list)[N]) {
	return list[MinIndex(list)];
}

template <typename T, size_t N>
size_t MaxIndex(const T (&list)[N]) {
	static_assert(N, "array can't be empty");

	size_t max = 0;

	for(size_t i = 0; i < N; i++)
		if(list[i] > list[max])
			max = i;

	return max;
}

template <typename T, size_t N>
T Max(const T (&list)[N]) {
	return list[MaxIndex(list)];
}