#include <Object/Base.hpp>

IObject::precision_type x1(const IObject& object)
{
    return object.location().x;
}

IObject::precision_type x2(const IObject& object)
{
    return object.location().x + object.width();
}

IObject::precision_type y1(const IObject& object)
{
    return object.location().y;
}

IObject::precision_type y2(const IObject& object)
{
    return object.location().y + object.height();
}
