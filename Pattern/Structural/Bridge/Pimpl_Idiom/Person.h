/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
#include <string>

class Person
{
public:
  Person();
  ~Person();
  void greet();
  
  // These has to be private as per standard, but event it's public client code can't see what's inside PersonImpl
  class PersonImpl;   // Forward declaration
  PersonImpl *impl; // bridge - not necessarily inner class, can vary (Important is forward-declared class)

private:
  std::string name;
};
