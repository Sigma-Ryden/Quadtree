#include <Object/Rectangle.hpp>

bool intersect(const Rectangle& A, const Rectangle& B)
{
    return cross(x1(A), x2(A), x1(B), x2(B)) and
           cross(y1(A), y2(A), y1(B), y2(B));
}

bool include(const Rectangle& area, const IObject& object)
{
    return x1(object) >= x1(area) and
           y1(object) >= y1(area)and
           x2(object) <= x2(area) and
           y2(object) <= y2(area);
}
