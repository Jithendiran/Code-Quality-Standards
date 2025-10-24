/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Factory.cpp -o /tmp/Factory

/*
As per separation of concerns we are going to make a specific class which will responsible only for creating the object
*/
#include <cmath>

enum class PointType
{
  cartesian,
  polar
};

class Point
{
public:
  Point(float x, float y) : x(x), y(y){}
private:
  float x, y;
};

// This is class is responsible only for creating the object of point
class PointFactory
{
  public:
  static Point NewCartesian(float x, float y)
  {
    return Point{ x,y };
  }

  static Point NewPolar(float r, float theta)
  {
    return Point{ r*cos(theta), r*sin(theta) };
  }
};

// here problem will be, user may not know there is a separate factory method available

int main()
{
    Point p = PointFactory::NewCartesian(5, 5);
    Point p2 = PointFactory::NewPolar(10, M_PI_4);
    return 0;
}