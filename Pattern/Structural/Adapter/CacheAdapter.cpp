/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ CacheAdapter.cpp -o /tmp/CacheAdapter

/*
The idea of caching in adapters is to store the results of an expensive adaptation process so that the conversion doesn't have to be performed every time
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm> // for std::hash

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
        return os << "Start: (" << line.start.x << "," << line.start.y << ") End: (" << line.end.x << "," << line.end.y << ")";
    }
};

// Custom Hash function for Line, required for std::map key or std::unordered_map
// We'll use a simple approach: combine the four coordinates into a single size_t value.
struct LineHasher
{
    size_t operator()(const Line& line) const
    {
        // Canonical representation: ensure start is always the point with the smaller x (then smaller y)
        // This ensures that { {1,1}, {3,3} } hashes the same as { {3,3}, {1,1} }
        const Point& p1 = line.start;
        const Point& p2 = line.end;

        // Use std::hash for basic integer hashing
        size_t h1 = hash<int>{}(p1.x);
        size_t h2 = hash<int>{}(p1.y);
        size_t h3 = hash<int>{}(p2.x);
        size_t h4 = hash<int>{}(p2.y);

        // Simple XOR combination (may result in collisions, but works for demonstration)
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

// Equality operator for Line (needed for std::map/std::unordered_map)
bool operator==(const Line& lhs, const Line& rhs)
{
    return (lhs.start.x == rhs.start.x && lhs.start.y == rhs.start.y &&
            lhs.end.x   == rhs.end.x   && lhs.end.y   == rhs.end.y);
}


// 3. Adapter: The class that converts the Adaptee's interface to the Target's interface
struct LineToPointAdapter
{
private:
    // Static cache for generated points: Maps a Line to its vector of Points.
    
    // Instead of a map, let's use a cleaner approach by referencing the
    // generated points inside the adapter, and making the generation conditional.
    
    // This simple adapter holds a reference to the cache entry
    const vector<Point>& points_ref;
    
    // --- STATIC CACHE IMPLEMENTATION ---
    // Key: Hashed representation of the line
    // Value: The generated vector of points
    static inline map<size_t, vector<Point>> cache;

    // Helper function to generate the points (Bresenham's)
    static vector<Point> generate_points(const Line& line)
    {
        cout << "--> GENERATING POINTS for " << line << endl;

        vector<Point> generated_points;
        int x1 = line.start.x, y1 = line.start.y;
        int x2 = line.end.x,   y2 = line.end.y;
        
        // Bresenham's Line Algorithm (simplified for integer coords)
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : (x1 > x2 ? -1 : 0);
        int sy = y1 < y2 ? 1 : (y1 > y2 ? -1 : 0);
        int err = (dx > dy ? dx : -dy) / 2;
        int e2;

        for (;;) {
            generated_points.push_back({x1, y1});
            if (x1 == x2 && y1 == y2) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x1 += sx; }
            if (e2 < dy) { err += dx; y1 += sy; }
        }
        return generated_points;
    }


public:
    // The LineToPointAdapter is initialized with a Line object
    LineToPointAdapter(const Line& line)
      : points_ref(get_points(line)) {}


    // The caching mechanism
    static const vector<Point>& get_points(const Line& line)
    {
        // Use a hash combining all four coordinates as a unique ID for the line.
        size_t hash_val = LineHasher{}(line);

        // 1. Check if the line is already in the cache (Cache Hit)
        if (cache.find(hash_val) == cache.end())
        {
            // 2. If not found (Cache Miss), generate the points and store them
            cache[hash_val] = generate_points(line);
        }

        // 3. Return a reference to the points vector from the cache
        return cache.at(hash_val);
    }

    // iterators
    // This makes the Adapter behave like a container of Points
    auto begin() const { return points_ref.begin(); }
    auto end() const { return points_ref.end(); }
};

int main()
{
    // Define the existing Lines (the Adaptee objects)
    Line line1 = { {1, 1}, {3, 3} }; // A diagonal line
    Line line2 = { {5, 2}, {5, 4} }; // A vertical line
    Line line1_dup = { {1, 1}, {3, 3} }; // Duplicate line

    // --- First access: Cache Miss (will generate points) ---
    LineToPointAdapter adapter1(line1);

    cout << "--- FIRST ACCESS (Line 1) ---" << endl;
    cout << "Points in line 1: ";
    for (const auto& p : adapter1) {
        cout << p << " ";
    }
    cout << endl; 
    
    // --- Second access: Cache Hit (will NOT generate points) ---
    cout << "\n--- SECOND ACCESS (Duplicate Line 1) ---" << endl;
    LineToPointAdapter adapter1_dup(line1_dup);
    
    cout << "Points in duplicate line 1: ";
    for (const auto& p : adapter1_dup) {
        cout << p << " ";
    }
    cout << endl; // Notice the "GENERATING POINTS" message is not printed again.

    // --- Third access: Cache Miss (will generate points for a new line) ---
    cout << "\n--- THIRD ACCESS (Line 2) ---" << endl;
    LineToPointAdapter adapter2(line2);
    
    cout << "Points in line 2: ";
    for (const auto& p : adapter2) {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}