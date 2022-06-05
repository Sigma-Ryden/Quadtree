#include <iostream> // cout

#include <Quadtree.hpp>
#include <Object/Circle.hpp>

void test()
{
    Quadtree quad = Quadtree(0, new Rectangle(8, 8), 1);

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

    auto area = Rectangle(2, 0, 6, 5);

    auto print_object = [](IObject* object)
    {
        for (int i = 0; i < object->height(); ++i, std::cout << '\n')
            for (int j = 0; j < object->width(); ++j)
                std::cout << "# ";

        std::cout << '\n';
    };

    iterate(&quad, &area, print_object);
}

int main()
{
    test();

    return 0;
}
