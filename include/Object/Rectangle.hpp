#ifndef OBJECT_RECTANGLE_HPP
#define OBJECT_RECTANGLE_HPP

#include <Object/Base.hpp>

class Rectangle : public IObject
{
private:
    Vector2 location_;
    Shape shape_;

public:
    Rectangle() noexcept : Rectangle(Vector2(), Shape()) {}

    Rectangle(const Vector2& location, const Shape& shape)
        : location_(location), shape_(shape) {}

    Rectangle(precision_type x, precision_type y, precision_type width, precision_type height)
        : location_(x, y), shape_(width, height) {}

    const Vector2& location() const noexcept override { return location_; }
    const Shape& shape() const noexcept override { return shape_; }
};

/*!
 * \brief Return true if area A intersects area B.
 */
bool intersect(const Rectangle& A, const Rectangle& B);

/*!
 * \brief Return true if area includes object.
 */
bool include(const Rectangle& area, const IObject& object);

#endif // OBJECT_RECTANGLE_HPP
