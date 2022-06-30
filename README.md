# Quadtree simple implementation

See the interface of the Quadtree [here](https://github.com/Sigma-Ryden/Quadtree/blob/master/include/Quadtree.hpp).

## Quick start:

Let's describe the area below with a tree:
```C++
7 . . . . . . . .
6 . . . . . . . .
5 . . . . # # # .
4 . . . . # # . .
3 # # # # # # . .
2 # # # # # # . .
1 # # # # . . . .
0 # # # # . . # #
  0 1 2 3 4 5 6 7
```

Since the Quadtree class is just a raw interface, let's include iostream for console output to display the result.
```C++
#include <Quadtree.hpp>

#include <iostream> // cout
```

Here is our test function:
```C++
void test()
{
    // Create an 8x8 level zero quadtree at the point (0, 0)
    // and set limit to 1-object in each node
    Quadtree quad = Quadtree(0, new Rectangle(0, 0, 8, 8), 1);

    quad.insert(new Rectangle(4, 4, 2, 2));
    quad.insert(new Rectangle(6, 5, 1, 1));

    quad.insert(new Rectangle(0, 0, 4, 4));

    quad.insert(new Rectangle(4, 2, 2, 2));

    quad.insert(new Rectangle(6, 0, 1, 1));
    quad.insert(new Rectangle(7, 0, 1, 1));

    // Create an 6x5 area, for the iteration by each object in
    // Note that: 6 - is width and 5 - is height of the area
    auto area = Rectangle(2, 0, 6, 5);

    auto print_object = [](IObject* object)
    {
        auto& shape = object->shape();

        for (int i = 0; i < shape.height; ++i, std::cout << '\n')
            for (int j = 0; j < shape.width; ++j)
                std::cout << "# ";

        std::cout << '\n';
    };

    // Print all objects wich includes given area 
    iterate(&quad, &area, print_object);
}
```
Let's run it:
```C++
int main()
{
    test();

    return 0;
}
```
Output:
```console
 # #
 # #

 #

 #
```
## Explanation:

Since we were created area like this:
```C++
auto area = Rectangle(2, 0, 6, 5);
```
It will hide only given area below:
```C++
4 . . # # . .
3 # # # # . .
2 # # # # . .
1 # # . . . .
0 # # . . # #
  2 3 4 5 6 7
```
But only 3 objects are fully included in the given area:
```C++
4 . . . . . .
3 . . # # . .
2 . . # # . .
1 . . . . . .
0 . . . . # #
  2 3 4 5 6 7
```

You can find other examples [here](https://github.com/Sigma-Ryden/Quadtree/tree/master/test).

## License:
This is an open source project licensed under: [MIT](https://opensource.org/licenses/MIT).
