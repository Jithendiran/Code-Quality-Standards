/*
 * Programmer: E.K.Jithendiran
 * Date: 26 Oct 2025
 */
// g++ -o /tmp/Geomentry Geomentry.cpp

/*
Here idea is to access the single object or composite (Big / Complex/ Group) object in the same way
*/

#include <iostream>
#include <vector>
#include <memory>

struct GraphicObject
{
    virtual void draw() = 0;
};

// single object
struct Circle : GraphicObject
{
    void draw() override
    {
        std::cout << "Circle" << std::endl;
    }
};

// composite object
struct Group : GraphicObject
{
    std::string name;

    explicit Group(const std::string &name)
        : name{name}
    {
    }

    void draw() override
    {
        std::cout << "Group " << name.c_str() << " contains:" << std::endl;
        for (auto &&o : objects)
            o->draw();
    }

    std::vector<GraphicObject *> objects;
};

int main()
{
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    // accessing composite object
    root.draw();
    // accessing the single object
    c1.draw();
}