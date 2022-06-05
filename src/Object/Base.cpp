#include <Object/Base.hpp>

IObject::precision_type width(const IObject& object)
{
    return object.shape().width;
}

IObject::precision_type height(const IObject& object)
{
    return object.shape().height;
}

IObject::precision_type x1(const IObject& object)
{
    return object.location().x;
}

IObject::precision_type x2(const IObject& object)
{
    return x1(object) + width(object);
}

IObject::precision_type y1(const IObject& object)
{
    return object.location().y;
}

IObject::precision_type y2(const IObject& object)
{
    return y1(object) + height(object);
}
