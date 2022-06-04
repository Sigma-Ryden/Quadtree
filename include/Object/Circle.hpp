#ifndef OBJECT_CIRCLE_HPP
#define OBJECT_CIRCLE_HPP

#include <Object/Base.hpp>

class Circle : public IObject
{
private:
    Vector2 location_;

    precision_type diameter_;

public:
    Circle() noexcept : Circle(0., 0., 0.) {}

    Circle(precision_type diameter)
        : Circle(0., 0., diameter) {}

    Circle(precision_type x, precision_type y, precision_type diameter)
        : location_(x, y), diameter_(diameter) {}

    const Vector2& location() const noexcept override { return location_; }

    precision_type width() const noexcept override { return diameter_; }
    precision_type height() const noexcept override { return diameter_; }
};

#endif // OBJECT_CIRCLE_HPP
