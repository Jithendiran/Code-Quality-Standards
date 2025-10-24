/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ AbstractFactory.cpp -o /tmp/AbstractFactory

/*
 * Here idea is to use a polymorphism for different types
 * Instead of single factory class, it will use a group of factory class
 */

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <functional>
using namespace std;

//---------------------------------------------------Data class
struct HotDrink
{
    virtual ~HotDrink() = default;

    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{

    void prepare(int volume) override
    {
        cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << endl;
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
    }
};

//--------------------------------------------------------Factory class
// Abstract factory class
struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};

// coffee factory
struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};

// Tea factory
struct TeaFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};

//---------------------------------------------concrete class for abstract factory

class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory()
    {
        // create each object with it's factory class
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string &name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};
// Functional factory
//--------------------------------------This type don't need seperate factory method for each type
class DrinkWithVolumeFactory
{
    // name, lambda function to create object
    map<string, function<unique_ptr<HotDrink>()>> factories;

public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = []
        {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["coffee"] = []
        {
            auto tea = make_unique<Coffee>();
            tea->prepare(200);
            return tea;
        };
    }

    unique_ptr<HotDrink> make_drink(const string &name);
};

inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string &name)
{
    return factories[name]();
}

//------------------------------------------------------instead of classes this is a simple alternative
unique_ptr<HotDrink> make_drink(string type)
{
  unique_ptr<HotDrink> drink;
  if (type == "tea")
  {
    drink = make_unique<Tea>();
    drink->prepare(200);
  }
  else 
  {
    drink = make_unique<Coffee>();
    drink->prepare(50);
  }
  return drink;
}

int main()
{
  auto d = make_drink("tea");

  DrinkFactory df;
  df.make_drink("coffee");

  return 0;
}