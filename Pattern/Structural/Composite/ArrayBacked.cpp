/*
 * Programmer: E.K.Jithendiran
 * Date: 26 Oct 2025
 */
// g++ -o /tmp/ArrayBacked ArrayBacked.cpp

#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>
using namespace std;

/*
Lets say we are creating a game, we have to introduce a creatures for the game, each creaters have sertain properties likesly (strength, agility,..)
*/
class CreatureLegacy
{
    int strength, agility, intelligence;
    // new property
    int charisma;

public:
    int get_strength() const
    {
        return strength;
    }

    void set_strength(int strength)
    {
        CreatureLegacy::strength = strength;
    }

    int get_agility() const
    {
        return agility;
    }

    void set_agility(int agility)
    {
        CreatureLegacy::agility = agility;
    }

    int get_intelligence() const
    {
        return intelligence;
    }

    void set_intelligence(int intelligence)
    {
        CreatureLegacy::intelligence = intelligence;
    }

    // sum, average, max.

    double sum() const
    {
        return strength + agility + intelligence;
    }

    double average() const
    {
        return sum() / 3.0;
    }

    int max() const
    {
        return ::max(::max(strength, agility), intelligence);
    }
};
/*
The problem with above approach is when we want to introduce a new ability or property we have to modify sum, average, max all the functions, it might be really painfull process
*/

// new way of implementation using composition
class Creature
{
    enum Abilities
    {
        str,
        agl,
        intl,
        count
    };
    array<int, count> abilities;
    /*
    [0] -> strength
    [1] -> agility
    [2] -> Intelligent
    [3] -> Total count of properties
    */

    // Here the getters and setters are kind of composite because we are accessing all the properties in the uniform way, but for client we are projecting as unique properties

public:
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value; }

    int get_agility() const { return abilities[agl]; }
    void set_agility(int value) { abilities[agl] = value; }

    int get_intelligence() const { return abilities[intl]; }
    void set_intelligence(int value) { abilities[intl] = value; }

    int sum() const
    {
        return accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const
    {
        return sum() / (double)count;
    }

    int max() const
    {
        return *max_element(abilities.begin(), abilities.end());
    }

    // if we want to introduce a new property it is really easy
    // No changes in sum, average amd max function is required
};

int main(int ac, char *av[])
{
    Creature orc;
    orc.set_strength(16);
    orc.set_agility(11);
    orc.set_intelligence(9);

    cout << "The orc has an average stat of "
         << orc.average()
         << " and a maximum stat of "
         << orc.max()
         << "\n";

    return 0;
}