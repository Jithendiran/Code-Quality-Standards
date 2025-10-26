/*
 * Programmer: E.K.Jithendiran
 * Date: 26 Oct 2025
 */
// g++ -o /tmp/Static Static.cpp

/*
Idea is to over come the issue in Dynamic decorator
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

struct Circle : Shape
{
  float radius;

  Circle(){}

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

  Square(){}

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


//-----------------------------------------------------
// Decorator

// note: class, not typename
template <typename T> struct ColoredShape2 : T
{
  static_assert(is_base_of<Shape, T>::value,
    "Template argument must be a Shape");

  string color;

  ColoredShape2(){}

  // Only color we are interseted in this class, reset are the base class, so it's been forwarded
  template <typename...Args>
  ColoredShape2(const string& color, Args ...args)
    : T(std::forward<Args>(args)...), color{color}
    // you cannot call base class constructor here
    // because you have no idea what it is, (so we are forward)
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T> struct TransparentShape2 : T
{
  uint8_t transparency;

  template<typename...Args>
  TransparentShape2(const uint8_t transparency, Args ...args)
    : T(std::forward<Args>(args)...), transparency{ transparency }
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has "
      << static_cast<float>(transparency) / 255.f * 100.f
      << "% transparency";
    return oss.str();
  }
};

int main(){
    ColoredShape2<Circle> green_circle{ "green" };
  green_circle.radius = 123;
  green_circle.resize(34);// here we can access 
  cout << green_circle.str() << endl;

  TransparentShape2<ColoredShape2<Square>> blue_invisible_square{ 0 };
  blue_invisible_square.color = "blue";
  blue_invisible_square.side = 321;
  cout << blue_invisible_square.str() << endl;
}