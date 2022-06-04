#ifndef OBJECT_CYRCLE_HPP
#define OBJECT_CYRCLE_HPP

#include <Object/Base.hpp>

class Cyrcle : public IObject
{
private:
    Vector2 location_;

    precision_type width_;
    precision_type height_;

public:
    Cyrcle() noexcept : Cyrcle(0., 0., 0., 0.) {}

    Cyrcle(precision_type width, precision_type height)
        : Cyrcle(0., 0., width, height) {}

    Cyrcle(precision_type x, precision_type y, precision_type width, precision_type height)
        : location_(x, y), width_(width), height_(height) {}

    const Vector2& location() const noexcept override { return location_; }

    precision_type width() const noexcept override { return width_; }
    precision_type height() const noexcept override { return height_; }
};

#endif // OBJECT_CYRCLE_HPP
