/*
 * Programmer: E.K.Jithendiran
 * Date: 25 Oct 2025
 */
// g++ -o Bridge Bridge.cpp

#include <iostream>
#include <memory>

// 1. The Implementation Hierarchy (Renderer/Draw Method)
/*
The Implementation Hierarchy focuses on the platform-specific details or drawing methods required to perform the low-level operations. This is often referred to as the Implementor side.

Defines how the operations declared in the Abstraction are carried out on a specific platform, system, or style.
*/
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render_circle() = 0;
    virtual void render_square() = 0;
};

// Concrete Implementations
class RasterRenderer : public Renderer {
public:
    void render_circle() override {
        std::cout << "  (Renderer) RASTER method used for Circle." << std::endl;
    }
    void render_square() override {
        std::cout << "  (Renderer) RASTER method used for Square." << std::endl;
    }
};

class VectorRenderer : public Renderer {
public:
    void render_circle() override {
        std::cout << "  (Renderer) VECTOR method used for Circle." << std::endl;
    }
    void render_square() override {
        std::cout << "  (Renderer) VECTOR method used for Square." << std::endl;
    }
};

// 2. The Abstraction Hierarchy (Shape)
/*
The Abstraction Hierarchy focuses on the conceptual entity and the high-level logic that the client code interacts with.

Defines what the object is and its general capabilities.
*/
class Shape {
protected:
    // The Bridge: holds a pointer to the Implementation
    std::unique_ptr<Renderer> renderer_;
public:
    Shape(std::unique_ptr<Renderer> api) : renderer_(std::move(api)) {}
    virtual ~Shape() = default;
    virtual void draw() = 0; 
};

// Refined Abstractions
class Circle : public Shape {
public:
    Circle(std::unique_ptr<Renderer> api) : Shape(std::move(api)) {}
    void draw() override {
        std::cout << "Drawing Circle..." << std::endl;
        // Delegation: Circle delegates the actual drawing work to its linked Renderer
        renderer_->render_circle();
    }
};

class Square : public Shape {
public:
    Square(std::unique_ptr<Renderer> api) : Shape(std::move(api)) {}
    void draw() override {
        std::cout << "Drawing Square..." << std::endl;
        // Delegation: Square delegates the actual drawing work to its linked Renderer
        renderer_->render_square();
    }
};


int main() {
     // Circle (Abstraction) is connected to a VectorRenderer (Implementation)
    std::unique_ptr<Shape> circle_vector = 
        std::make_unique<Circle>(std::make_unique<VectorRenderer>());
    circle_vector->draw();

    std::cout << "---" << std::endl;

    // Square (Abstraction) is connected to a RasterRenderer (Implementation)
    std::unique_ptr<Shape> square_raster = 
        std::make_unique<Square>(std::make_unique<RasterRenderer>());
    square_raster->draw();

    // Benefit: Adding a new shape (Triangle) only requires adding the Triangle class 
    // and two simple methods to the Renderer interface (render_triangle).
    return 0;
}