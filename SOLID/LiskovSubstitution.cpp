/*
 * Programmer: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ LiskovSubstitution.cpp -o /tmp/LiskovSubstitution

/*
Liskov Substitution
If a function takes a base class, any derived class of the base class should pass to the function without any issue
*/

#include <iostream>

class Rectangle
{
protected:
    int width, height;

public:
    Rectangle(const int width, const int height)
        : width{width}, height{height} {}

    int get_width() const { return width; }
    virtual void set_width(const int width) { this->width = width; }
    int get_height() const { return height; }
    virtual void set_height(const int height) { this->height = height; }

    int area() const { return width * height; }
};

// as per math, we can create square by rectangle
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}
    void set_width(const int width) override
    {
        this->width = height = width; // setting both width and height 
    }
    void set_height(const int height) override
    {
        this->height = width = height; // setting both width and height 
    }
};


void process(Rectangle &r)
{
    int w = r.get_width();
    r.set_height(10);

    std::cout << "expected area = " << (w * 10)
              << ", got " << r.area() << std::endl;
}

int main()
{
    Rectangle r{5, 5};
    process(r);

    // It is failing here, It is not valid as per Liskov Substitution
    Square s{5};
    process(s);

    return 0;
}