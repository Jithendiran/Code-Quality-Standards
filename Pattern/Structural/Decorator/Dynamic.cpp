/*
 * Programmer: E.K.Jithendiran
 * Date: 26 Oct 2025
 */
// g++ -o /tmp/Dynamic Dynamic.cpp

/*
Idea is to add the additional capability to shapes like (color and transparent) dynamically
*/

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct Shape
{
    virtual string str() const = 0;
};

// actual class
struct Circle : Shape
{
    float radius;

    Circle() {}

    explicit Circle(const float radius)
        : radius{radius}
    {
    }

    void resize(float factor)
    {
        radius *= factor;
    }

    string str() const override
    {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}

    explicit Square(const float side)
        : side{side}
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << "A square of with side " << side;
        return oss.str();
    }
};

// decorator class
struct ColoredShape : Shape
{
    Shape &shape;
    string color;

    ColoredShape(Shape &shape, const string &color)
        : shape{shape},
          color{color}
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape &shape;
    uint8_t transparency;

    TransparentShape(Shape &shape, const uint8_t transparency)
        : shape{shape},
          transparency{transparency}
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main()
{
    Square sq{5};
    ColoredShape red_sq{sq, "Red"};
    TransparentShape trans_red_sq{red_sq, 2};

    cout << sq.str() << endl;
    cout << red_sq.str() << endl;
    
    cout << trans_red_sq.str() << endl;
    // circle
    Circle ci{2};
    ci.resize(4); // resizing
    ColoredShape bl_ci{ci, "Blue"};
    // bl_ci.resize(5); // Error
    // why error ? because core circle object is wrapped with ColoredShape, it doesn't have resize method
    // Compiler can't find the resize method
}