#include <Quadtree.hpp>
#include <Object/Circle.hpp>

int main()
{
    Quadtree quad = Quadtree(0, Rectangle(600, 400), 1);

    quad.insert(new Circle(150));
    quad.insert(new Rectangle(30, 45));

    return 0;
}
