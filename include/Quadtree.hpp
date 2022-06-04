#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <array> // array

#include <Object/Base.hpp>
#include <Object/Rectangle.hpp>

#include <Container.hpp>

class Quadtree
{
public:
    using size_type = std::size_t;
    using index_type = int;

private:
    static constexpr size_type number_of_nodes = 4;

    const size_type max_objects_in_node_;
    const size_type max_depth_level_;

    index_type level_;
    Rectangle area_;

    Container<IObject*> objects_;

    std::array<Quadtree*, number_of_nodes> nodes_;

public:
    Quadtree(
        index_type level,
        const Rectangle& area,
        size_type max_objects_in_node = 16,
        size_type max_depth_level = 8);

    Quadtree(const Quadtree&) = default;
    Quadtree(Quadtree&&) noexcept = default;

    ~Quadtree();

public:
    /*!
    Clears the Quadtree
    */
    void clear();

    /*!
    Insert the object into the Quadtree. If the node
    exceeds the capacity, it will split and add all
    objects to their corresponding nodes.
    */
    void insert(IObject* object);

    /*!
    Return all objects that could collide with the given object
    */
    auto retrieve(Container<IObject*>& objects, IObject* object) -> Container<IObject*>&;

private:
    /*!
    Splits the node into 4 subnodes
    */
    void split();

    /*!
    Determine which node the object belongs to. -1 means
    object cannot completely fit within a child node and is part
    of the parent node
    */
    index_type getIndex(IObject* object);
};

#endif // QUAD_TREE_HPP
