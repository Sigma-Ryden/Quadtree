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

#endif // IOBJECT_HPP
