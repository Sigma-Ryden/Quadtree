#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <Detail/Meta.hpp>

template <typename T, typename enable = void>
struct Shape;

template <typename T>
struct Shape<T, meta::when<std::is_arithmetic<T>::value>>
{
    using precision_type = T;

    precision_type width;
    precision_type height;

    Shape() : width(0.), height(0.) {}
    Shape(precision_type width, precision_type height)
        : width(width), height(height) {}
};

#endif // SHAPE_HPP
