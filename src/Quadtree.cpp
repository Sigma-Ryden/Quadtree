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

// will be repair
int Quadtree::index(IObject* object)
{
    index_type index = -1;

    auto obj_x1 = x1(*object);
    auto obj_y1 = y1(*object);

    auto obj_x2 = x2(*object);
    auto obj_y2 = y2(*object);

    auto horizontal_point = x1(*area);
    auto vertical_point   = y1(*area);

    auto horizontal_whole_point = x2(*area);
    auto vertical_whole_point   = y2(*area);

    auto horizontal_mid_point = horizontal_point + width(*area) * 0.5;
    auto vertical_mid_point   = vertical_point + height(*area) * 0.5;

    // Object can completely fit within the top quadrants
    bool top_quadrant = (obj_y1 >= vertical_mid_point and obj_y2 <= vertical_whole_point);

    // Object can completely fit within the bottom quadrants
    bool bottom_quadrant = (obj_y1 >= vertical_point and obj_y2 <= vertical_mid_point);

    // Object can completely fit within the left quadrants
    bool left_quadrant = (obj_x1 >= horizontal_point and obj_x2 <= horizontal_mid_point);

    // Object can completely fit within the right quadrants
    bool right_quadrant = (obj_x1 >= horizontal_mid_point and obj_x2 <= horizontal_whole_point);

    if (top_quadrant and right_quadrant)
        index = 0;

    else if (top_quadrant and left_quadrant)
        index = 1;

    else if (bottom_quadrant and left_quadrant)
        index = 2;

    else if (bottom_quadrant and right_quadrant)
        index = 3;

    return index;
}

void Quadtree::insert(IObject* object)
{
    index_type idx;
    if (nodes_[0] != nullptr) // checking for child nodes
    {
        idx = index(object);

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
            idx = index(objects_[i]);
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

void reach(Quadtree* quad, IObject* object, Container<IObject*>& storage)
{
    auto idx = quad->index(object);

    auto& nodes = quad->nodes();

    if (idx != -1 and nodes[0] != nullptr)
        reach(nodes[idx], object, storage);

    storage.add(quad->objects());
}
