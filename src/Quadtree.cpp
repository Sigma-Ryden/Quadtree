#include <Quadtree.hpp>

Quadtree::Quadtree(
    index_type level,
    const Rectangle& area,
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
}

void Quadtree::clear()
{
    objects_.clear();

    for (size_type i = 0; i < nodes_.size(); ++i)
    {
        if (nodes_[i] != nullptr)
        {
            nodes_[i]->clear();
            nodes_[i] = nullptr;
        }
    }
}

// will be repair
int Quadtree::index(IObject* object)
{
    index_type index = -1;

    auto obj_x1 = object->location().x;
    auto obj_y1 = object->location().y;

    auto obj_x2 = obj_x1 + object->width();
    auto obj_y2 = obj_y1 + object->height();

    auto horizontal_point = area.location().x;
    auto vertical_point   = area.location().y;

    auto horizontal_whole_point = horizontal_point + area.width();
    auto vertical_whole_point   = vertical_point + area.height();

    auto horizontal_mid_point = horizontal_point + area.width() * 0.5;
    auto vertical_mid_point   = vertical_point + area.height() * 0.5;

    // Object can completely fit within the top quadrants
    bool top_quadrant = (obj_y1 > vertical_mid_point and obj_y2 < vertical_whole_point);

    // Object can completely fit within the bottom quadrants
    bool bottom_quadrant = (obj_y1 > vertical_point and obj_y2 < vertical_mid_point);

    // Object can completely fit within the left quadrants
    bool left_quadrant = (obj_x1 > horizontal_point and obj_x2 < horizontal_mid_point);

    // Object can completely fit within the right quadrants
    bool right_quadrant = (obj_x1 > horizontal_mid_point and obj_x2 < horizontal_whole_point);

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
    if (nodes_[0] != nullptr) // checking for nodes
    {
        index_type idx = index(object);

        if (idx != -1)
        {
            nodes_[idx]->insert(object);
            return;
        }
    }

    objects_.add(object);

    if (objects_.size() > threshold and level < max_level)
    {
        split();

        size_type i = 0;
        while (i < objects_.size())
        {
            auto idx = index(objects_[i]);

            if (idx != -1)
            {
                nodes_[idx]->insert(objects_[i]);
                objects_.remove(i);
            }
            else  ++i;
        }
    }
}

auto Quadtree::retrieve(Container<IObject*>& objects, IObject* object) -> Container<IObject*>&
{
    auto idx = index(object);

    if (idx != -1 && nodes_[0] != nullptr)
        nodes_[idx]->retrieve(objects, object);

    objects.add(objects_);

    return objects;
}

auto Quadtree::retrieve(IObject* object) -> Container<IObject*>
{
    Container<IObject*> objects;
    objects.reserve(threshold);

    retrieve(objects, object);

    return objects;
}

void Quadtree::split()
{
    auto mid_w = area.width() * 0.5;
    auto mid_h = area.height() * 0.5;

    auto x = area.location().x;
    auto y = area.location().y;

    // Order:
    //  II  I
    // III IV

    nodes_[0] = new Quadtree(level + 1, Rectangle(x + mid_w, y + mid_h, mid_w, mid_h));
    nodes_[1] = new Quadtree(level + 1, Rectangle(x, y + mid_h, mid_w, mid_h));

    nodes_[2] = new Quadtree(level + 1, Rectangle(x, y, mid_w, mid_h));
    nodes_[3] = new Quadtree(level + 1, Rectangle(x + mid_w, y, mid_w, mid_h));
}
