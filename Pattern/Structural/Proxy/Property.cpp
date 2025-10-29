/*
 * Programmer: E.K.Jithendiran
 * Date: 28 Oct 2025
 */
// g++ -o /tmp/Property Property.cpp

/*
Idea here is to get proxy of getter and setter without creating getter and setter and actual class
We should access the getter and setter as a normal proerty
*/

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

// proxy class
template <typename T> struct Property
{
  T value;
  Property(const T initialValue)
  {
    *this = initialValue;
  }

  // This will act as a getter
  operator T()
  {
    cout<<"Retrivel -> "<<endl;
    return value;
  }

  // assignment operator
  // this act as a setter
  T operator =(T newValue)
  {
    cout<<"Assignment = "<<endl;
    return value = newValue;
  }
};

struct Creature
{
  Property<int> strength{ 10 }; // This called assignment
  Property<int> agility{ 5 };// This called assignment
};

int main()
{
  Creature creature;
  creature.agility = 20; // This called assignment
  // how this is proxy?
  /*
  Because i'm access strength and agility as data member
  */
  cout << creature.agility << endl;
}
