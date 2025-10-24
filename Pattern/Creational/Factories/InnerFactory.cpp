/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ InnerFactory.cpp -o /tmp/InnerFactory

/*
Here the idea is to bring the factory class inside the class
*/

#include <cmath>

enum class PointType
{
    cartesian,
    polar
};

class Point
{
    // use a factory method
    Point(float x, float y) : x(x), y(y) {}

    class PointFactory
    {
        PointFactory() {}

    public:
        static Point NewCartesian(float x, float y)
        {
            return {x, y};
        }
        static Point NewPolar(float r, float theta)
        {
            return {r * cos(theta), r * sin(theta)};
        }
    };

public:
    float x, y;
    static PointFactory Factory;
};

int main()
{
    // will not work
    // Point p{ 1,2 };

    // nope!
    // Point::PointFactory pf;

    // if factory is public, then
    // auto p = Point::PointFactory::NewCartesian(3, 4);

    // at any rate, use this
    auto pp = Point::Factory.NewCartesian(2, 3);

    return 0;
}

// It might violate Open-close principle if new type is introduced