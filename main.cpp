#include <Quadtree.hpp>
#include <Object/Cyrcle.hpp>

int main()
{
    Quadtree quad = Quadtree(0, Rectangle(600, 600), 1);

    quad.insert(new Cyrcle(12, 12));
    quad.insert(new Rectangle(30, 45));

    return 0;
}
