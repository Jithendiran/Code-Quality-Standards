/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Prototype.cpp -o /tmp/Prototype

/*
Idea is to do the deep copy of all the objects
*/

#include <string>
#include <iostream>
using namespace std;

struct Address
{
    string street;
    string city;
    int floor;

    Address(const string &street, const string &city, const int floor)
        : street{street},
          city{city},
          floor{floor} {}

    
    Address(const Address& other)
    : street{other.street},
      city{other.city},
      floor{other.floor}
  {
  }

    friend ostream &operator<<(ostream &os, const Address &obj)
    {
        return os
               << "street: " << obj.street
               << " city: " << obj.city
               << " floor: " << obj.floor;
    }

};

struct Contact
{
    string name;
    Address *address;

    Contact(const string &name, Address *address) : name(name), address(address) {}

Contact(const Contact &other)
        : name{other.name}, 
          address{ new Address{*other.address} } // <--- DEEP COPY: Create a NEW Address object 
    {
    }

    friend ostream &operator<<(ostream &os, const Contact &obj)
    {
        return os
               << "name: " << obj.name
               << " works at " << *obj.address; // note the star here
    }
};

int main()
{
    Contact John{"John", new Address{"123 East Dr", "London", 1}};
    Contact Jane = John;
    Jane.name = "Jane";
    Jane.address->floor = 5;
    // Imporove by making a global contact with default values and use that for cloning

    cout << John << endl << Jane << endl;
}