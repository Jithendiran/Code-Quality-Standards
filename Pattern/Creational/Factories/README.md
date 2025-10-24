# Factories

* **Primary Goal**: To create different types of objects (products) that share a common interface.

* **Focus**: What object to create. (The object's type.)

* **Process**: One-step creation. You call one method, and a fully configured object is returned immediately.

* **When to Use**: When the client code doesn't know which specific class it needs (e.g., a VehicleFactory that returns a Car, Truck, or Motorcycle).

**Analogy**
Ordering from a vending machine : You put in money and press 'Coke', and you get a Coke. You don't care how the machine picked it.

## Problem

What is the problem without factory pattern?

[Problem](./Problem.cpp)

## Table of content
1. [Factory method](./FactoryMethod.cpp)
2. [Factory](./Factory.cpp)
3. [Inner Factory](./InnerFactory.cpp)
4. [Abstract Factory](./AbstractFactory.cpp)