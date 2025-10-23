/*
 * Author: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ OpenClosed.cpp -o /tmp/OpenClosed
/*
* Open Closed
Open to extension and closed for modification, Avoid the code which is already written, extension means extending the functionality by inheritance

existing class should not be modified, a new class is accepted

Why existing class should not modify?
The existing/(already written) class is already tested and used by many class. If mofification happened we have retest class from scratch and needs to modify which ever class is affected
*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum class Color
{
    red,
    green,
    blue
};
enum class Size
{
    small,
    medium,
    large
};

struct Product
{
    string name;
    Color color;
    Size size;
};

//--------------------------------------NON-OCP-------------------------------
// problem with this approach for each new filter have to modify the existing class
struct ProductFilter
{
    typedef vector<Product *> Items;

    Items by_color(Items items, const Color color)
    {
        Items result;
        for (auto &i : items)
            if (i->color == color)
                result.push_back(i);
        return result;
    }

    Items by_size(Items items, const Size size)
    {
        Items result;
        for (auto &i : items)
            if (i->size == size)
                result.push_back(i);
        return result;
    }

    Items by_size_and_color(Items items, const Size size, const Color color)
    {
        Items result;
        for (auto &i : items)
            if (i->size == size && i->color == color)
                result.push_back(i);
        return result;
    }

    // if need new filter for or condition needs to modify this class
};

//------------------------------------------------OCP--------------------------
// suggessted approach
// this is a generic method

//----------------------------Declaration

// Specification is the condition to be met
// AKA Specification pattern
template <typename T>
struct Specification
{
    virtual ~Specification() = default;
    virtual bool is_satisfied(T *item) const = 0; // if the condition met, return true
};

// filter the item based on the specification
template <typename T>
struct Filter
{
    virtual vector<T *> filter(vector<T *> items,
                               Specification<T> &spec) = 0;
};

//------------combination of filter

template <typename T>
struct AndSpecification;

// better one for and (&&) condition
template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second)
{
    return {first, second};
}

//-------------------------------------------Implementation
struct BetterFilter : Filter<Product>
{
    vector<Product *> filter(vector<Product *> items,
                             Specification<Product> &spec) override
    {
        vector<Product *> result;
        for (auto &p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

// filter options

struct ColorSpecification : Specification<Product>
{
    Color color;

    ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product *item) const override
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    explicit SizeSpecification(const Size size)
        : size{size}
    {
    }

    bool is_satisfied(Product *item) const override
    {
        return item->size == size;
    }
};

// This can be skipped if the language support operator over loading
template <typename T>
struct AndSpecification : Specification<T>
{
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first, const Specification<T> &second)
        : first(first), second(second) {}

    bool is_satisfied(T *item) const override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

//---------------------------------------

int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const vector<Product *> all{&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecification green(Color::green); // defining the color filter

    auto green_things = bf.filter(all, green);
    for (auto &x : green_things)
        cout << x->name << " is green\n";

    /*
       Apple is green
       Tree is green
    */

    SizeSpecification large(Size::large); // defining the size filter

    AndSpecification<Product> green_and_large(green, large); // and filter

    auto big_green_things = bf.filter(all, green_and_large);
    for (auto &x : big_green_things)
        cout << x->name << " is large and green\n";

    // Tree is large and green

    // use the operator instead (same for || etc.)
    auto spec = green && large; // operator overloading, alternative for AndSpecification
    for (auto &x : bf.filter(all, spec))
        cout << x->name << " is green and large\n";

    // Tree is green and large
    // warning: the following will compile but will NOT work, why?
    // auto spec2 = SizeSpecification{Size::large} &&
    //              ColorSpecification{Color::blue};
    // for (auto &x : bf.filter(all, spec2))
    //     cout << x->name << " is blue and large\n";

    return 0;
}