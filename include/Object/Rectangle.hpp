#ifndef OBJECT_RECTANGLE_HPP
#define OBJECT_RECTANGLE_HPP

#include <Object/Base.hpp>

class Rectangle : public IObject
{
private:
    Vector2 location_;

    precision_type width_;
    precision_type height_;

public:
    Rectangle() noexcept : Rectangle(0., 0., 0., 0.) {}

    Rectangle(precision_type width, precision_type height)
        : Rectangle(0., 0., width, height) {}

    Rectangle(precision_type x, precision_type y, precision_type width, precision_type height)
        : location_(x, y), width_(width), height_(height) {}

    const Vector2& location() const noexcept override { return location_; }

    precision_type width() const noexcept override { return width_; }
    precision_type height() const noexcept override { return height_; }
};

#endif // OBJECT_RECTANGLE_HPP
