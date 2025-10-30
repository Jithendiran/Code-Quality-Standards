/*
 * Programmer: E.K.Jithendiran
 * Date: 29 Oct 2025
 */
// g++ Pointers.cpp -o /tmp/Pointers
/*
Idea is we are developing a game
We introduce a creature, creature has sereval ability, we handle those ability in chain of responsibility
*/

#include <iostream>
#include <string>
using namespace std;

// Data
struct Creature
{
  string name;
  int attack, defense;

  Creature(const string& name, const int attack, const int defense)
    : name(name),
      attack(attack),
      defense(defense)
  {
  }


  friend ostream& operator<<(ostream& os, const Creature& obj)
  {
    return os
      << "name: " << obj.name
      << " attack: " << obj.attack
      << " defense: " << obj.defense;
  }
};

// Chain of responsibility class
class CreatureModifier
{
    // Linked list root
  CreatureModifier* next{ nullptr }; // unique_ptr
protected:
  Creature& creature; // pointer or shared_ptr
public:
  explicit CreatureModifier(Creature& creature)
    : creature(creature)
  {
  }
  virtual ~CreatureModifier() = default;

  void add(CreatureModifier* cm)
  {
    if (next) next->add(cm);
    else next = cm;
  }


  virtual void handle()
  {
    // calling next responsibility if present
    if (next) next->handle();
  }
};

// No bonuses can be applied to this creature

class NoBonusesModifier : public CreatureModifier
{
public:
  explicit NoBonusesModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }

  void handle() override
  {
    // Reject the responsibility
  }
};

// Double the creature's attack
class DoubleAttackModifier : public CreatureModifier
{
public:
  explicit DoubleAttackModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }

  void handle() override
  {
    creature.attack *= 2;
    CreatureModifier::handle();
  }
};

// Increase defense by 1 unless power > 2
class IncreaseDefenseModifier : public CreatureModifier
{
public:
  explicit IncreaseDefenseModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }


  void handle() override
  {
    if (creature.attack <= 2)
      creature.defense += 1;
    CreatureModifier::handle();
  }
};

int main()
{
  Creature goblin{ "Goblin", 1, 1 };
  CreatureModifier root{ goblin };
  DoubleAttackModifier r1{ goblin };
  DoubleAttackModifier r1_2{ goblin };
  IncreaseDefenseModifier r2{ goblin };
  //NoBonusesModifier nb{ goblin }; // effectively Command objects

  //root.add(&nb);
  root.add(&r1);
  root.add(&r1_2);
  root.add(&r2);

  root.handle();

  cout << goblin << endl;
  return 0;
}
