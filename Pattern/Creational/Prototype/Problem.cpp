/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Problem.cpp -o /tmp/Problem

/*
Imagine company owns a building, based on the employee professional they allocted to diffent floor, for each emplyee in the address part only floor number may vary
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

    friend ostream &operator<<(ostream &os, const Address &obj)
    {
        return os
               << "street: " << obj.street
               << " city: " << obj.city
               << " suite: " << obj.floor;
    }
};

struct Contact
{
    string name;
    Address *address;

    Contact(const string &name, Address *address) : name(name), address(address) {}

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
    Contact Jade{"Jade", new Address{"123 East Dr", "London", 2}};
    Contact Jemma{"Jemma", new Address{"123 East Dr", "London", 2}};
    // Here the problem is while creating the object address object creation is overwhelming

    // simply fix
    Contact Jane = John;
    Jane.name = "Jane";
    Jane.address->floor = 5;

    // here problem is if john of jane change the professional, it will affect both because of same pointer

    cout << John << endl
         << Jane << endl;
}