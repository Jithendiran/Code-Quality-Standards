/*
 * Programmer: E.K.Jithendiran
 * Date: 24 Oct 2025
 */
// g++ -o person_app Person.cpp main.cpp
#include "Person.h"
#include <iostream>

int main() {
    
    Person alice;
    
    std::cout << "Testing Person class using Pimpl Idiom:\n";
    
    alice.greet();

    std::cout << "\nProgram finished.\n";

    // Error
    // alice.impl->greet(&alice); // it can't see impl's greet method
    
    return 0;
}