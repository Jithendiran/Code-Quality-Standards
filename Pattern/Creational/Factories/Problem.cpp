/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Problem.cpp -o /tmp/Problem

// Life without factories

/*
There are several types of Graphs coordinates available example (cartesian, polar)
cartesian deals with plain surface, it's points are in x and y
polar deals with circular surface, it's point are in rho and theta
*/

#include<cmath>
struct  Point_1
{
    float x,y;
    
    // when i need to create a cartesian points i will specify x and y in constructor
    Point_1(float x, float y): x(x), y(y) {}

    // This is for polar ponts
    Point_1(float rho, float theta) {
        x = rho * cos(theta);
        y = rho * sin(theta);
    }

    // This is not a valid constructor overload because both exactly has 2 float parameter
};

// Temperaory fix

enum class PointType {
    cartestian,
    polar
};

struct Point{
    float x, y; 

    /*
    Here we fix the issue by additional param type, depends on the type object will be created

    But there is a small problem here
    why param name is a and b not as (x,y) or (rho, theta)?
    Since it is a generic constructor if we give name as x and y, if user want to create polar type, they will confuse is x is rho or y is rho, there is no clear guidence.

    Comments or document can help a little bit, but still it will confuse
    */
    Point( float a, float b, PointType type = PointType::cartestian){
        if (type == PointType::cartestian){
            x = a;
            y = b;
        } else {
            x = a * cos(b);
            y = a * sin(b);
        }
    }

};
