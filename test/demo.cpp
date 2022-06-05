#include <random> // rand
#include <ctime> // time

#include <utility> // forward
#include <iostream> // cout

#include <Quadtree.hpp>
#include <Object/Circle.hpp>
#include <Random.hpp>

enum class ObjectType
{
    Undefined,
    Rectangle,
    Circle
};

IObject* make_object(ObjectType object_type, IObject::Vector2 location, IObject::Shape shape)
{
    switch (object_type)
    {
    case ObjectType::Rectangle:
        return new Rectangle(location, shape);

    case ObjectType::Circle:
        return new Circle(location, shape);

    default:
        return nullptr;
    }
}

void generate_2d_level(std::size_t width, std::size_t height, std::size_t number_of_objects)
{
    Quadtree quad = Quadtree(0, new Rectangle(0, 0, width, height), 4);

    Random<IObject::precision_type> real_gen;
    Random<int> gen;

    for (std::size_t i = 0; i < number_of_objects; ++i)
    {
        auto object_type = static_cast<ObjectType>(gen(1, 2)); // generate 1 or 2

        auto x = real_gen(0.0, width);
        auto y = real_gen(0.0, height);
        auto w = real_gen(0.1, width / (i + 0.25));
        auto h = real_gen(0.1, height / (i + 0.25));

        auto location = IObject::Vector2(x, y);
        auto shape    = IObject::Shape(w, h);

        quad.insert(make_object(object_type, location, shape));
    }

    auto print_node_level = [](Quadtree* node)
    {
        std::cout << node->level << '\n';
    };

    std::size_t count = 0;
    auto objects_count = [&](Quadtree* node)
    {
        count += node->objects().size();
    };

    iterate(&quad, print_node_level);
    iterate(&quad, objects_count);

    std::cout << "Total objects: " << count << '\n';
}

int main()
{
    generate_2d_level(16, 16, 30);

    return 0;
}
