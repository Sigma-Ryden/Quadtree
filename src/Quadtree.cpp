#include <Quadtree.hpp>

Quadtree::Quadtree(
    index_type level,
    const Rectangle& area,
    size_type max_objects_in_node,
    size_type max_depth_level)
        : level_(level), area_(area), objects_(), nodes_()
        , max_objects_in_node_(max_objects_in_node)
        , max_depth_level_(max_depth_level)
{
    objects_.reserve(max_objects_in_node_);
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

    for (size_type i = 0; i < number_of_nodes; ++i)
    {
        if (nodes_[i] != nullptr)
        {
            nodes_[i]->clear();
            nodes_[i] = nullptr;
        }
    }
}

void Quadtree::split()
{
    auto mid_w = area_.width() * 0.5;
    auto mid_h = area_.height() * 0.5;

    auto x = area_.location().x;
    auto y = area_.location().y;

    // Order:
    //  II  I
    // III IV

    // Mapping
    // (1, 0) (1, 1)
    // (0, 0) (1, 0)

    // I at the (1, 1)
    nodes_[0] = new Quadtree(level_ + 1, Rectangle(x + mid_w, y + mid_h, mid_w, mid_h));

     // II at the (1, 0)
    nodes_[1] = new Quadtree(level_ + 1, Rectangle(x, y + mid_h, mid_w, mid_h));

    // III at the (0, 0)
    nodes_[2] = new Quadtree(level_ + 1, Rectangle(x, y, mid_w, mid_h));

    // IV at the (0, 1)
    nodes_[3] = new Quadtree(level_ + 1, Rectangle(x + mid_w, y, mid_w, mid_h));
}

// will be repair
int Quadtree::getIndex(IObject* object)
{
    index_type index = -1;

    auto x = object->location().x;
    auto y = object->location().y;

    auto width  = x + object->width();
    auto height = y + object->height();
    //
    auto horizontal_point = area_.location().x;
    auto vertical_point   = area_.location().y;

    auto horizontal_whole_point = horizontal_point + area_.width();
    auto vertical_whole_point   = vertical_point + area_.height();

    auto horizontal_mid_point = horizontal_point + area_.width() * 0.5;
    auto vertical_mid_point   = vertical_point + area_.height() * 0.5;

    // Object can completely fit within the top quadrants
    bool top_quadrant = (y > vertical_mid_point and height < vertical_whole_point);

    // Object can completely fit within the bottom quadrants
    bool bottom_quadrant = (y > vertical_point and height < vertical_mid_point);

    // Object can completely fit within the left quadrants
    if (x < horizontal_mid_point and x + width < horizontal_mid_point)
    {
        if (top_quadrant)
            index = 1;

        else if (bottom_quadrant)
            index = 2;
    }
    // Object can completely fit within the right quadrants
    else if (x > horizontal_mid_point and x + width < horizontal_whole_point)
    {
        if (top_quadrant)
            index = 0;

        else if (bottom_quadrant)
            index = 3;
    }
    //
    return index;
}

void Quadtree::insert(IObject* object)
{
    if (nodes_[0] != nullptr) // checking for nodes
    {
        index_type index = getIndex(object);

        if (index != -1)
        {
            nodes_[index]->insert(object);
            return;
        }
    }

    objects_.add(object);

    if (objects_.size() > max_objects_in_node_ and level_ < max_depth_level_)
    {
        split();

        size_type i = 0;
        while (i < objects_.size())
        {
            auto index = getIndex(objects_[i]);

            if (index != -1)
            {
                nodes_[index]->insert(objects_[i]);
                objects_.remove(i);
            }
            else  ++i;
        }
    }
}

auto Quadtree::retrieve(Container<IObject*>& objects, IObject* object) -> Container<IObject*>&
{
    auto index = getIndex(object);

    if (index != -1 && nodes_[0] != nullptr)
        nodes_[index]->retrieve(objects, object);

    objects.add(objects_);

    return objects;
}
