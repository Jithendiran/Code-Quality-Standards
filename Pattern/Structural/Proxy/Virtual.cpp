/*
 * Programmer: E.K.Jithendiran
 * Date: 28 Oct 2025
 */
// g++ -o /tmp/Virtual Virtual.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

struct Image
{
    virtual ~Image() = default;
    virtual void draw() = 0;
};

// This is the actual object
struct Bitmap : Image
{
    Bitmap(const string &filename)
    {
        cout << "Loading image from " << filename << endl;
    }

    void draw() override
    {
        cout << "Drawing image" << endl;
    }
};

/*
We need one proxy class, which should look like actal class and loading should only happen when user is calling draw function
*/
struct LazyBitmap : Image
{
    // It is storing the file
    LazyBitmap(const string &filename) : filename(filename) {}
    ~LazyBitmap() { delete bmp; }

    // It is init the object if not created and call the draw
    void draw() override
    {
        if (!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap *bmp{nullptr};
    string filename;
};

int main()
{
    Bitmap img0{"Pikachu.png"};
    img0.draw();
    LazyBitmap img{"pokemon.png"};
    img.draw(); // loaded whether the bitmap is loaded or not
    img.draw();
}