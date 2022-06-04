#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <array> // array

#include <Object/Base.hpp>
#include <Object/Rectangle.hpp>

#include <Container.hpp>

class Quadtree
{
public:
    using size_type                 = std::size_t;
    using index_type                = int;

    template <typename T>
    using Array                     = std::array<T, 4>;

private:
    Array<Quadtree*> nodes_;        ///< Array of the child node
    Container<IObject*> objects_;   ///< All objects located in the quadtree

public:
    const Rectangle area;           ///< The aree used by the quadtree

    const size_type level;          ///< The level of the quadtree
    const size_type max_level;      ///< Max depth level of the subnode
    const size_type threshold;      ///< Max objects in the quadtree

public:
    Quadtree(index_type level,
             const Rectangle& area,
             size_type max_objects_in_node = 16,
             size_type max_depth_level = 8);

    Quadtree(const Quadtree&) = default;
    Quadtree(Quadtree&&) noexcept = default;

    ~Quadtree();

public:    
    /*!
    Return all objects in the quadtree.
    */
    auto objects() const noexcept -> const Container<IObject*>& { return objects_; }

    /*!
    Return container of child nodes.
    */
    auto nodes() const noexcept -> const Array<Quadtree*> { return nodes_; }

    /*!
    Clears the quadtree.
    */
    void clear();

    /*!
    Inserts the object into the child node if it fits,
    otherwise the object will be added to the parent node.
    */
    void insert(IObject* object);

    /*!
    Return all objects that could collide with the given object.
    */
    auto retrieve(Container<IObject*>& objects, IObject* object) -> Container<IObject*>&;
    auto retrieve(IObject* object) -> Container<IObject*>;

    /*!
    Returns the index of the child node in which the object resides.
    Otherwise, returns -1 if the object is in the parent node.
    */
    auto index(IObject* object) -> index_type;

private:
    /*!
    Splits the node into 4 subnodes.
    */
    void split();
};

#endif // QUAD_TREE_HPP
