/*
 * Author: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ DependencyInversion.cpp -o /tmp/DependencyInversion

/*
Dependency Inversion is based on two ideas
1. High-level modules should not depend on low-level modules.
   Both should depend on abstractions.
2. Abstractions should not depend on concrete/implentation class/ detail class.
   concrete/implentation class/ detail class should depend on abstractions.

why Abstraction?
    Instead of depending on concrete type, depend on a generic type.
    If we depend on the concrete type, we are depending on the implementation details, which may not suitable
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

//------------------------------------NON-DI

struct HiRelationships // low-level
{
    // why this is low level?
    /*
    Because it has data and some basic utility to populate the data
    */
    vector<tuple<Person, Relationship, Person>> relations;
    void add_parent_and_child(const Person &parent, const Person &child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }
};

struct RelationResearch // High-level
{
    RelationResearch(HiRelationships &relationships)
    {
        auto &relations = relationships.relations; // if low-leve deceided to make private, this may not work
        // if low level data structure change, auto &&[first, rel, second] it may not work
        for (auto &&[first, rel, second] : relations)
        {
            if (first.name == "John" && rel == Relationship::parent)
            {
                cout << "John has a child called " << second.name << endl;
            }
        }
    }
};

/*
The above RelationResearch may work, if some thing changed in low level class, high level call will break

Let's say 
* Instead of vector<tuple>, low level class decided to use different data structure like plain vector
* Low level class planned to change relations property as private,.. etc
* Needs add new relation called child and sibling, here we have to change the low level class

the cases like above will break the high level class
*/

//------------------------------------DI

struct RelationshipBrowser
{
  // This is the generic API which is exposed, which will not change in future 
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // low-level
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research // high-level
{
    // High level is not depend on the low level implementation detail like vector<tuple>, instead it is depend on abstract/generic type, which won't change
    // find_all_children_of this api always return only vector<Person>
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      cout << "John has a child called " << child.name << endl;
    }
  }
};

int main()
{
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}