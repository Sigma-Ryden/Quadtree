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

    using Indexing                  = index_type (Quadtree::*)(IObject*) const;

private:
    Array<Quadtree*> nodes_;        ///< Array of the child node
    Container<IObject*> objects_;   ///< All objects located in the quadtree

public:
    const Rectangle* area;          ///< The aree used by the quadtree

    const size_type level;          ///< The level of the quadtree
    const size_type max_level;      ///< Max depth level of the subnode
    const size_type threshold;      ///< Max objects in the quadtree

public:
    Quadtree(index_type level,
             Rectangle* area,
             size_type max_objects_in_node = 16,
             size_type max_depth_level = 8);

    Quadtree(const Quadtree&) = default;
    Quadtree(Quadtree&&) noexcept = default;

    ~Quadtree();

public:    
    /*!
     * \brief Return all objects in the quadtree.
     */
    const Container<IObject*>& objects() const noexcept { return objects_; }

    /*!
     * \brief Return container of child nodes.
     */
    const Array<Quadtree*> nodes() const noexcept { return nodes_; }

    /*!
     * \brief Clears the quadtree.
     */
    void clear();

    /*!
     * \brief Inserts the object into the child node if it fits.
     * Otherwise the object will be added to the parent node.
     */
    void insert(IObject* object, Indexing indexing = &Quadtree::index);

    /*!
     * \brief Returns the index of the child node in which the object `fully` resides.
     * Otherwise, returns -1 if the object is in the parent node.
     */
    index_type index(IObject* object) const noexcept;

    /*!
     * \brief Returns the index of the child node in which the object `partially` resides.
     * Otherwise, returns -1 if the object is in the parent node.
     */
    index_type weak_index(IObject* object) const noexcept;

private:
    /*!
     * \brief Splits the node into 4 subnodes.
     */
    void split();
};

/*!
 * \brief Save all objects into the container, that could collide with the given object.
 */
void reach(
    Quadtree* quadtree,
    IObject* object,
    Container<IObject*>& objects,
    Quadtree::Indexing indexing = &Quadtree::index);

/*!
 * \brief Return all objects that could collide with the given object.
 */
Container<IObject*> reach(
    Quadtree* quadtree,
    IObject* object,
    Quadtree::Indexing indexing = &Quadtree::index);

/*!
 * \brief Iteration by the quatree nodes.
 */
template <class Function,
          meta::require<meta::is_callable<Function, Quadtree*>::value> = 0>
void iterate(Quadtree* quadtree, Function function)
{
    if (quadtree == nullptr)
        return;

    function(quadtree);

    for (const auto& node : quadtree->nodes())
        iterate(node, function);
}

/*!
 * \brief Iteration by the objects in the certain area of the quadtree.
 */
template <class Function, class Capture,
          meta::require<meta::is_callable<Function, IObject*>::value and
                        meta::is_callable<Capture, const Rectangle&, const IObject&>::value> = 0>
void iterate(Quadtree* quadtree, Rectangle* area, Function function, Capture capture = include_all)
{
    if (quadtree == nullptr)
        return;

    if (intersect(*quadtree->area, *area))
    {
        for (auto& object : quadtree->objects())
        {
            if (capture(*area, *object))
                function(object);
        }
    }

    for (const auto& node : quadtree->nodes())
        iterate(node, area, function);
}

#endif // QUAD_TREE_HPP
