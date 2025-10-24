/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ -c Person.cpp -o /tmp/Person
#include "Person.h"

// Implementation class structure
class Person::PersonImpl
{
public:
    void greet(Person *p);
};

// Implementation class private function, it is hidden to clients
void Person::PersonImpl::greet(Person *p)
{
    printf("hello %s", p->name.c_str());
}

Person::Person(): impl(new PersonImpl){}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet(this);
}
