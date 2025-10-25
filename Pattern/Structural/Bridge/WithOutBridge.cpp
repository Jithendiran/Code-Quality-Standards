/*
 * Programmer: E.K.Jithendiran
 * Date: 25 Oct 2025
 */
// g++ -o /tmp/WithOutBridge WithOutBridge.cpp

/*
This program is for demonstrating without bridge

Shapes - Circle, Square
Method to draw - Raster, Vector
*/

#include <iostream>
#include <memory>

// 1. Base Abstraction/Shape
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() = 0;
};

// 2. Concrete Classes (Combinatorial Explosion)

// --- Circle / Raster combination ---
class RasterCircle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle using RASTER (dots/pixels)." << std::endl;
    }
};

// --- Circle / Vector combination ---
class VectorCircle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle using VECTOR (lines/curves)." << std::endl;
    }
};

// --- Square / Raster combination ---
class RasterSquare : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Square using RASTER (dots/pixels)." << std::endl;
    }
};

// --- Square / Vector combination ---
class VectorSquare : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Square using VECTOR (lines/curves)." << std::endl;
    }
};

int main() {
    
    std::unique_ptr<Shape> s1 = std::make_unique<RasterCircle>();
    s1->draw();

    std::unique_ptr<Shape> s2 = std::make_unique<VectorSquare>();
    s2->draw();

    // Problem: If you add Triangle (new Shape), you need RasterTriangle and VectorTriangle (2 new classes).
    // If you add Printer (new Method), you need PrinterCircle, PrinterSquare (2 new classes).
}