#pragma once

#include <cassert>
#include "math/vector4.hpp"
#include "math/vector3.hpp"
#include "math/functions.hpp"

// Row Major Matrix
template <typename T>
struct Matrix4{
    Vector4<T> Rows[4];

    // Identity Matrix
    constexpr Matrix4(const T &ident = T(1));

    constexpr Matrix4(const Vector4<T> &row0,
                      const Vector4<T> &row1,
                      const Vector4<T> &row2,
                      const Vector4<T> &row3);
    
    constexpr Vector4<T> &operator[](size_t index);

    constexpr const Vector4<T> &operator[](size_t index)const;

    constexpr Vector4<T> Row(size_t index)const;

    constexpr Vector4<T> Column(size_t index)const;

    constexpr T& Flat(size_t index);

    constexpr const T& Flat(size_t index)const;
};

template <typename T>
constexpr Matrix4<T>::Matrix4(const T &i):
    Rows{{i,0,0,0},
         {0,i,0,0},
         {0,0,i,0},
         {0,0,0,i}}
{}

template <typename T>
constexpr Matrix4<T>::Matrix4(
    const Vector4<T> &row0,
    const Vector4<T> &row1,
    const Vector4<T> &row2,
    const Vector4<T> &row3):
        Rows{row0, row1, row2, row3}
{}

template<typename T>
constexpr Vector4<T> &Matrix4<T>::operator[](size_t index){
    return const_cast<Vector4<T>&>(const_cast<const Matrix4<T>*>(this)->operator[](index));
}

template <typename T>
constexpr const Vector4<T> &Matrix4<T>::operator[](size_t index)const{
    assert(index < 4 && index >= 0 && "Matrix4: Can't address move than 4 rows"); 
    return Rows[index];
}
template <typename T>
constexpr Vector4<T> Matrix4<T>::Column(size_t index) const{
    return { Rows[0][index], Rows[1][index], Rows[2][index], Rows[3][index] };
}

template <typename T>
constexpr Vector4<T> Matrix4<T>::Row(size_t index) const{
    return Rows[index];
}

template <typename T>
constexpr const T &Matrix4<T>::Flat(size_t index) const{
    return (&Rows[0][0])[index];
}
template <typename T>
constexpr T &Matrix4<T>::Flat(size_t index) {
    return (&Rows[0][0])[index];
}
template <typename T>
constexpr Matrix4<T> operator*(const Matrix4<T> &l, const Matrix4<T> &r){
    Matrix4<T> res{T{}};
    for(size_t i = 0; i<4; i++)
        for(size_t j = 0; j<4; j++)
            res[i][j] = Math::Dot(l.Row(i), r.Column(j));    
    return res;
}

template <typename T>
constexpr Vector4<T> operator*(const Matrix4<T> &l, const Vector4<T> &r){
    return {
        Math::Dot(l.Row(0), r),
        Math::Dot(l.Row(1), r),
        Math::Dot(l.Row(2), r),
        Math::Dot(l.Row(3), r)
    };
}

typedef Matrix4<float> Matrix4f;
typedef Matrix4<s32> Matrix4s;
typedef Matrix4<u32> Matrix4u;    
