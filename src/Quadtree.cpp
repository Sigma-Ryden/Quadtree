#include <Quadtree.hpp>

Quadtree::Quadtree(
    index_type level,
    Rectangle* area,
    size_type max_objects_in_node,
    size_type max_depth_level)
        : nodes_()
        , objects_()
        , area(area)
        , level(level)
        , threshold(max_objects_in_node)
        , max_level(max_depth_level)
{
    objects_.reserve(threshold);
}

Quadtree::~Quadtree()
{
    for (auto& object : objects_)
        delete object;

    for (auto& node : nodes_)
        delete node;

    delete area;
}

void Quadtree::clear()
{
    objects_.clear();

    for (auto& node : nodes_)
    {
        if (node != nullptr)
        {
            node->clear();
            node = nullptr;
        }
    }
}

Quadtree::index_type Quadtree::index(IObject* object) const noexcept
{
    auto obj_x1 = x1(*object);
    auto obj_y1 = y1(*object);
    auto obj_x2 = x2(*object);
    auto obj_y2 = y2(*object);

    auto horizontal_point     = x1(*area);
    auto vertical_point       = y1(*area);
    auto horizontal_end_point = x2(*area);
    auto vertical_end_point   = y2(*area);
    auto horizontal_mid_point = centerX(*area);
    auto vertical_mid_point   = centerY(*area);

    // Object can completely fit within the `side` quadrants
    bool top_quadrant    = obj_y1 >= vertical_mid_point and obj_y2 <= vertical_end_point;
    bool bottom_quadrant = obj_y1 >= vertical_point and obj_y2 <= vertical_mid_point;
    bool left_quadrant   = obj_x1 >= horizontal_point and obj_x2 <= horizontal_mid_point;
    bool right_quadrant  = obj_x1 >= horizontal_mid_point and obj_x2 <= horizontal_end_point;

    if (top_quadrant and right_quadrant)
        return 0;

    else if (top_quadrant and left_quadrant)
        return 1;

    else if (bottom_quadrant and left_quadrant)
        return 2;

    else if (bottom_quadrant and right_quadrant)
        return 3;

    return -1;
}

Quadtree::index_type Quadtree::weak_index(IObject* object) const noexcept
{
    auto obj_x = centerX(*object);
    auto obj_y = centerY(*object);

    auto horizontal_point     = x1(*area);
    auto vertical_point       = y1(*area);
    auto horizontal_end_point = x2(*area);
    auto vertical_end_point   = y2(*area);
    auto horizontal_mid_point = centerX(*area);
    auto vertical_mid_point   = centerY(*area);

    // Object can partially fit within the `side` quadrants
    bool top_quadrant    = obj_y > vertical_mid_point and obj_y < vertical_end_point;
    bool bottom_quadrant = obj_y > vertical_point and obj_y < vertical_mid_point;
    bool left_quadrant   = obj_x > horizontal_point and obj_x < horizontal_mid_point;
    bool right_quadrant  = obj_x > horizontal_mid_point and obj_x < horizontal_end_point;

    if (top_quadrant and right_quadrant)
        return 0;

    else if (top_quadrant and left_quadrant)
        return 1;

    else if (bottom_quadrant and left_quadrant)
        return 2;

    else if (bottom_quadrant and right_quadrant)
        return 3;

    return -1;
}

void Quadtree::insert(IObject* object, Indexing indexing)
{
    index_type idx;
    if (nodes_[0] != nullptr) // checking for child nodes
    {
        idx = (this->*indexing)(object);

        if (idx != -1)
            nodes_[idx]->insert(object);

        return;
    }

    objects_.add(object);

    if (objects_.size() > threshold and level < max_level)
    {
        if (nodes_[0] == nullptr) split();

        size_type i = 0;
        while (i < objects_.size())
        {
            idx = (this->*indexing)(objects_[i]);
            if (idx != -1)
            {
                nodes_[idx]->insert(objects_[i]);
                objects_.remove(i);
            }
            else
            {
                ++i;
            }
        }
    }
}

void Quadtree::split()
{
    auto mid_w = width(*area) * 0.5;
    auto mid_h = height(*area) * 0.5;

    auto x = x1(*area);
    auto y = y1(*area);

    // Order:
    //  II  I
    // III IV

    nodes_[0] = new Quadtree(level + 1, new Rectangle(x + mid_w, y + mid_h, mid_w, mid_h), threshold, max_level);
    nodes_[1] = new Quadtree(level + 1, new Rectangle(x, y + mid_h, mid_w, mid_h), threshold, max_level);

    nodes_[2] = new Quadtree(level + 1, new Rectangle(x, y, mid_w, mid_h), threshold, max_level);
    nodes_[3] = new Quadtree(level + 1, new Rectangle(x + mid_w, y, mid_w, mid_h), threshold, max_level);
}

void reach(
    Quadtree* quad,
    IObject* object,
    Container<IObject*>& storage,
    Quadtree::Indexing indexing)
{
    auto idx = (quad->*indexing)(object);

    auto& nodes = quad->nodes();

    if (idx != -1 and nodes[0] != nullptr)
        reach(nodes[idx], object, storage);

    storage.add(quad->objects());
}

Container<IObject*> reach(
    Quadtree* quad,
    IObject* object,
    Quadtree::Indexing indexing)
{
    Container<IObject*> storage;
    storage.reserve(quad->objects().size());

    reach(quad, object, storage, indexing);

    return storage;
}
