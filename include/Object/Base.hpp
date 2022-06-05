#ifndef OBJECT_BASE_HPP
#define OBJECT_BASE_HPP

#include <Vector2.hpp>

class IObject
{
public:
    using precision_type = float;

    using Vector2 = Vector2<precision_type>;

public:
    virtual ~IObject() = default;

    virtual const Vector2& location() const noexcept = 0;
    virtual precision_type width() const noexcept = 0;
    virtual precision_type height() const noexcept = 0;
};

IObject::precision_type x1(const IObject& object);
IObject::precision_type x2(const IObject& object);
IObject::precision_type y1(const IObject& object);
IObject::precision_type y2(const IObject& object);

#endif // IOBJECT_HPP
