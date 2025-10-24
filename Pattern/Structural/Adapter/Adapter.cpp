/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Adapter.cpp -o /tmp/Adapter

/*
Ponits has two values x and y
Lines has start and end points

We have lines, but we need the points to work with, create a adapter which will create the points for lines
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 1. Target Interface: What the client wants (a collection of Points)
struct Point
{
    int x, y;
    friend ostream& operator<<(ostream& os, const Point& p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

// 2. Adaptee: The class we are adapting (the existing Line class)
struct Line
{
    Point start, end;

    friend ostream& operator<<(ostream& os, const Line& line)
    {
        return os << "Start: (" << line.start.x << "," << line.start.y << ") End: (" << line.end.x << line.end.y <<")";
    }
};

// 3. Adapter: The class that converts the Adaptee's interface to the Target's interface
// Interface means port, surface,.. not the programming interface
struct LineToPointAdapter
{
private:
    vector<Point> points;

public:
    // The LineToPointAdapter is initialized with a Line object
    LineToPointAdapter(const Line& line)
    {

        // Get start and end coordinates
        int x1 = line.start.x;
        int y1 = line.start.y;
        int x2 = line.end.x;
        int y2 = line.end.y;


        // Bresenham'salgorithm would be used here.
        // For simplicity, we'll only handle vertical/horizontal lines
        // and fill the gaps.
        
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : (x1 > x2 ? -1 : 0);
        int sy = y1 < y2 ? 1 : (y1 > y2 ? -1 : 0);
        int err = (dx > dy ? dx : -dy) / 2;
        int e2;

        for (;;) {
            points.push_back({x1, y1});
            if (x1 == x2 && y1 == y2) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x1 += sx; }
            if (e2 < dy) { err += dx; y1 += sy; }
        }
    }

    // iterators
    // This makes the Adapter behave like a container of Points
    auto begin() const { return points.begin(); }
    auto end() const { return points.end(); }
};

int main()
{
    // Define the existing Lines (the Adaptee objects)
    Line line1 = { {1, 1}, {3, 3} }; // A diagonal line
    Line line2 = { {5, 2}, {5, 4} }; // A vertical line

    // Create the Adapter object
    LineToPointAdapter adapter1(line1);
    LineToPointAdapter adapter2(line2);

    cout << "Points in line 1: ";
    
    for (const auto& p : adapter1)
    {
        cout << p << " ";
    }
    cout << endl; // Output: (1,1) (2,2) (3,3) 

    cout << "Points in line 2: ";
    for (const auto& p : adapter2)
    {
        cout << p << " ";
    }
    cout << endl; // Output: (5,2) (5,3) (5,4) 
    
    return 0;
}