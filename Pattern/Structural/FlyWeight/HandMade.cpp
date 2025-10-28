/*
 * Programmer: E.K.Jithendiran
 * Date: 27 Oct 2025
 */
// g++ -o /tmp/HandMade HandMade.cpp

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
using namespace boost;

struct User
{
    string name;
}; // this is a bad design because lot of user name have common first name and last name

typedef u_int32_t key;

/*
bimap is a map data structure, it has the ability to search value based on Key and search key based on value

left.find() -> search by key, return value
right.find -> search by value, return key
*/
struct UserName
{
    UserName(const string &first_name, const string &last_name)
        : first_name{add(first_name)}, last_name{add(last_name)}
    {
    }

    const string &get_first_name() const
    {
        return names.left.find(last_name)->second;
    }

    const string &get_last_name() const
    {
        return names.left.find(last_name)->second;
    }

    static void info()
    {
        for (auto entry : names.left)
        {
            cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const UserName &obj)
    {
        return os
               << "first_name: " << obj.first_name << " " << obj.get_first_name()
               << " last_name: " << obj.last_name << " " << obj.get_last_name();
    }

protected:
    static bimap<key, string> names;
    static int seed;

    static key add(const string &s)
    {
        auto it = names.right.find(s);
        if (it == names.right.end())
        {
            // add it
            key id = ++seed;
            names.insert(bimap<key, string>::value_type(seed, s));
            return id;
        }
        return it->second;
    }
    key first_name, last_name;
};

int UserName::seed = 0;
bimap<key, string> UserName::names{};

int main()
{
    User us1{"John Doe"};
    User us2{"John smith"};

    //-----------------------------------
    UserName john_doe{"John", "Doe"};
    UserName jane_doe{"Jane", "Doe"};

    cout << "John " << john_doe << endl;
    cout << "Jane " << jane_doe << endl;

    UserName::info();
    //-----------------------------------
}