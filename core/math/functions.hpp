#pragma once

#include <cmath>
#include <cassert>
#include <float.h>
#include "vector3.hpp"
#include "vector4.hpp"

namespace Math{

constexpr double Pi = 3.14159265368979323;

template<typename NumberType>
constexpr NumberType Epsilon() {
    assert(false && "Epsilon is not implemented for this type");
    return NumberType();
}

template<>
constexpr float Epsilon<float>() {
    return FLT_EPSILON;
}

template<typename NumberType>
constexpr NumberType Abs(NumberType radians){
    return std::abs(radians);
}

template<typename NumberType>
bool IsNearlyEqual(NumberType a, NumberType b, NumberType epsilon = Epsilon<NumberType>()) {
    return Abs(a - b) <= epsilon;
}
template<typename NumberType>
bool IsInRange(NumberType value, NumberType min, NumberType max) {
    return value <= max && value >= min;
}

template<typename NumberType>
constexpr NumberType Sin(NumberType radians){
    return sin(radians);
}

template<typename NumberType>
constexpr NumberType Cos(NumberType radians){
    return cos(radians);
}

template<typename NumberType>
constexpr NumberType Tan(NumberType radians){
    return tan(radians);
}

template<typename NumberType>
constexpr NumberType Cot(NumberType radians){
    return Tan(NumberType(Pi/2.0) - radians);
}

template<typename NumberType>
constexpr NumberType Asin(NumberType radians){
    return asin(radians);
}

template<typename NumberType>
constexpr NumberType Acos(NumberType radians){
    return acos(radians);
}
template<typename NumberType>
constexpr NumberType Atan(NumberType radians){
    return atan(radians);
}
template<typename NumberType>
constexpr NumberType Atan2(NumberType y_radians, NumberType x_radians){
    return atan2(y_radians, x_radians);
}

template<typename NumberType>
constexpr NumberType Deg(NumberType radians){
    return static_cast<NumberType>(radians / NumberType(Pi) * NumberType(180.0));
}

template<typename NumberType>
constexpr NumberType Rad(NumberType degrees){
    return static_cast<NumberType>(degrees / NumberType(180.0) * NumberType(Pi));
}

template <typename NumberType, typename = decltype(float(*(NumberType*)nullptr))>
float Sqrt(NumberType number) {
    return sqrtf((float)number);
}

inline double Sqrt(double number) {
    return sqrt(number);
}

template <typename IntegerType>
constexpr IntegerType AlignUp(IntegerType number, IntegerType alignment) {
    return number + (alignment - number % alignment) % alignment;
}

template <typename IntegerType>
constexpr IntegerType AlignDown(IntegerType number, IntegerType alignment) {
    return number - number % alignment;
}

template <typename NumberType>
constexpr NumberType Clamp(NumberType number, NumberType lower, NumberType upper) {
    if(number > upper)
        return upper;
    if(number < lower)
        return lower;
    return number;
}


template <typename T>
constexpr T Dot(const Vector3<T> &left, const Vector3<T> &right){
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template <typename T>
constexpr T Dot(const Vector4<T> &left, const Vector4<T> &right){
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

template <typename T>
Vector3<T> Cross(const Vector3<T>& vec1, const Vector3<T>& vec2) {
    return {
    vec1[1] * vec2[2] - vec1[2] * vec2[1],
    vec1[2] * vec2[0] - vec1[0] * vec2[2],
    vec1[0] * vec2[1] - vec1[1] * vec2[0]
    };
}

template<typename T>
constexpr T Lerp(const T &f, const T &s, float c){
    return f + (s - f)*c;
}

template<typename T, typename ResultT = decltype(T{} / Vector3<T>{}.Length())>
constexpr Vector3<ResultT> Normalize(const Vector3<T> &vector){
    auto length = vector.Length();

    return Vector3<ResultT>{vector.x / length, vector.y / length, vector.z / length};
}


}//namespace Math::
