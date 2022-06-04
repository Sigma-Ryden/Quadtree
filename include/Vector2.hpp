#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <Detail/Meta.hpp>

template <typename T, typename enable = void>
struct Vector2;

template <typename T>
struct Vector2<T, meta::when<std::is_arithmetic<T>::value>>
{
    using precision_type = T;

    precision_type x;
    precision_type y;

    Vector2() : x(0.), y(0.) {}
    Vector2(precision_type x, precision_type y) : x(x), y(y) {}
};

#endif // VECTOR2_HPP
