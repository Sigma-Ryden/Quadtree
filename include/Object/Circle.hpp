#ifndef OBJECT_CIRCLE_HPP
#define OBJECT_CIRCLE_HPP

#include <Object/Base.hpp>

class Circle : public IObject
{
private:
    Vector2 location_;
    Shape shape_;

public:
    Circle() noexcept : Circle(Vector2(), Shape()) {}

    Circle(const Vector2& location, const Shape& shape)
        : location_(location), shape_(shape) {}

    Circle(precision_type x, precision_type y, precision_type width, precision_type height)
        : location_(x, y), shape_(width, height) {}

    const Vector2& location() const noexcept override { return location_; }
    const Shape& shape() const noexcept override { return shape_; }
};

#endif // OBJECT_CIRCLE_HPP
