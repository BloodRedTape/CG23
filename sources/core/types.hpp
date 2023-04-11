#pragma once

#include <cstdint>
#include <cstddef>

typedef std::int8_t s8;
typedef std::uint8_t u8;
typedef std::int16_t s16;
typedef std::uint16_t u16;
typedef std::int32_t s32;
typedef std::uint32_t u32;
typedef std::int64_t s64;
typedef std::uint64_t u64;

typedef u8 byte;

typedef std::size_t size_t;

template <typename T, size_t N>
constexpr size_t lengthof(T (&)[N]){
    return N;
}
