#include <iostream> // cout

#include <Quadtree.hpp>
#include <Object/Circle.hpp>

int main()
{
    Quadtree quad = Quadtree(0, Rectangle(20, 30), 1);

    quad.insert(new Circle(2, 3, 5));
    quad.insert(new Circle(3, 2, 3));
    quad.insert(new Circle(2, 2, 2));
    quad.insert(new Circle(3, 3, 1));
    quad.insert(new Circle(3, 3, 0.5));

    quad.insert(new Rectangle(7, 1, 7, 2));
    quad.insert(new Rectangle(3, 2, 2, 2));

    quad.insert(new Circle(2, 2, 5));
    quad.insert(new Rectangle(17, 15, 1, 1));

    auto f = [](Quadtree* quadtree)
    {
        std::cout << quadtree->level << '\n';
    };

    iterate(&quad, f);

    return 0;
}
