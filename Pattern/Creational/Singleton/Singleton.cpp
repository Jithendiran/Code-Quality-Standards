/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ Singleton.cpp -o /tmp/Singleton

#include <iostream>

class Singleton {
private:
    // 1. Private Constructor: Stops direct creation
    Singleton() {
        std::cout << "Singleton created (only once)." << std::endl;
    }

    // 2. Delete copy operations: Stops cloning and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 3. Public Static Access Method
    static Singleton& getInstance() {
        // The instance is created the first time this function is called.
        // C++ guarantees this initialization is thread-safe.
        static Singleton instance;
        return instance;
    }

    void do_something() const {
        std::cout << "Singleton is active." << std::endl;
    }
};

// --- Usage ---
int main() {
    // Access the single instance
    Singleton::getInstance().do_something();

    // Access the same instance again (constructor is NOT called again)
    Singleton::getInstance().do_something();

    return 0;
}