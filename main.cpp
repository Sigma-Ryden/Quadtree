#include <iostream> // cout

#include <Quadtree.hpp>
#include <Object/Circle.hpp>

void test()
{
    Quadtree quad = Quadtree(0, Rectangle(8, 8), 1);

    /*
    7 . . . . . . . .
    6 . . . . . . . .
    5 . . . . # # # .
    4 . . . . # # . .
    3 # # # # # # . .
    2 # # # # # # . .
    1 # # # # . . . .
    0 # # # # . . # #
      0 1 2 3 4 5 6 7
    */
    quad.insert(new Rectangle(4, 4, 2, 2));
    quad.insert(new Rectangle(6, 5, 1, 1));

    quad.insert(new Rectangle(0, 0, 4, 4));

    quad.insert(new Rectangle(4, 2, 2, 2));

    quad.insert(new Rectangle(6, 0, 1, 1));
    quad.insert(new Rectangle(7, 0, 1, 1));

    auto f = [](Quadtree* quadtree)
    {
        std::cout << quadtree->level << '\n';
    };

    iterate(&quad, f);
}

int main()
{
    test();

    return 0;
}
