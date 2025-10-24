/*
 * Programmer: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ Facets.cpp -o /tmp/Facets
/*Facets
Facets refers to the practice of splitting a single, complex object's construction logic into multiple, specialized builder classes.
The primary purpose of using facets is to make the builder pattern more manageable, modular, and context-specific for the user.

When we have more complex object creation, we can split the builder into several builder, which work together

The building process is split across several builder classes, each focusing on a specific part of the $\mathbf{Person}$ object—these are the facets.
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

// data class
class Person
{
    // address
    std::string street_address, post_code, city;

    // employment
    std::string company_name, position;
    int annual_income = 0;

    // private default constructor
    // preventing direct incomplete construction of object
    Person()
    {
        std::cout << "Person created\n";
    }

public:
    ~Person()
    {
        std::cout << "Person destroyed\n";
    }

    static PersonBuilder create();

    // don't confuse here---not important
    // param move constructor
    Person(Person &&other)
        : street_address{move(other.street_address)},
          post_code{move(other.post_code)},
          city{move(other.city)},
          company_name{move(other.company_name)},
          position{move(other.position)},
          annual_income{other.annual_income}
    {
    }

    // copy constructor
    Person &operator=(Person &&other)
    {
        if (this == &other)
            return *this;
        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = move(other.position);
        annual_income = other.annual_income;
        return *this;
    }
    // don't confuse here---not important

    // function for printing
    friend std::ostream &operator<<(std::ostream &os, const Person &obj)
    {
        return os
               << "street_address: " << obj.street_address
               << " post_code: " << obj.post_code
               << " city: " << obj.city
               << " company_name: " << obj.company_name
               << " position: " << obj.position
               << " annual_income: " << obj.annual_income;
    }

    // many builders for same data class
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};

// This is the abstract base class for all facets, All facet methods operate on this same Person object.
class PersonBuilderBase
{
protected:
    Person &person;
    explicit PersonBuilderBase(Person &person)
        : person{person}
    {
    }

public:
    // It allows the final builder object (which inherits from this base) to be implicitly converted to the completed Person object when assigned to a Person variable
    operator Person() const
    {
        return std::move(person);
    }

    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
    Person p; // it create's the object

public:
    PersonBuilder() : PersonBuilderBase{p}
    {
    }
};

class PersonAddressBuilder : public PersonBuilderBase
{
    typedef PersonAddressBuilder Self;

public:
    explicit PersonAddressBuilder(Person &person)
        : PersonBuilderBase{person}
    {
    }

    Self &at(std::string street_address)
    {
        person.street_address = street_address;
        return *this;
    }

    Self &with_postcode(std::string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    Self &in(std::string city)
    {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder Self;

public:
    explicit PersonJobBuilder(Person &person)
        : PersonBuilderBase{person}
    {
    }

    Self &at(std::string company_name)
    {
        person.company_name = company_name;
        return *this;
    }

    Self &as_a(std::string position)
    {
        person.position = position;
        return *this;
    }

    Self &earning(int annual_income)
    {
        person.annual_income = annual_income;
        return *this;
    }
};

//  This is the first builder returned by Person::create().
PersonBuilder Person::create()
{
    return PersonBuilder{};
}

// Building the address components.
PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder{person};
}

// Building the employment components.
PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{person};
}

int main()
{
    Person p = Person::create()
                   .lives().at("123 London Road")
                           .with_postcode("SW1 1GB")
                           .in("London")
                   .works().at("PragmaSoft")
                           .as_a("Consultant")
                           .earning(10e6);

    cout << p << endl;
    return 0;
}