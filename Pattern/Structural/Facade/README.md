# Facade

* **Primary Goal**: To provide a simplified, unified interface to a complex subsystem of classe

* **Focus**: Simplification and Decoupling. It focuses on hiding the complexity and promoting loose coupling between the client code and the subsystem.

* **Process**: Wrapping a Subsystem. It is a single wrapper class that contains references to the complex subsystem objects

* **When to Use**: 
    * When you have a large number of interdependent classes that are difficult to use or understand.
    * When you need to decouple a client from the implementation details of a complex subsystem.
    * To structure a system into layers, using a facade as the entry point to each layer.

**Analogy**
Ordering a meal at a Restaurant: 

The Customer (Client) doesn't interact directly with the dozens of complex systems needed to prepare and serve the food (the stove, the pantry, the recipe books, the dishwasher, etc.). Instead, the customer interacts with a single entity: the Waiter (Facade).

The Waiter (Facade):
1. Provides a simple menu (a simple interface, like orderFood('steak')).
2. Knows how to coordinate the complex steps: telling the Kitchen (Subsystem) what to cook, telling the Bar (Subsystem) to prepare a drink, and fetching the final meal.

Client : The Customer
Facade: The Waiter
Subsystem Classes: The Chef, Kitchen, Pantry, Dishwasher,..

## Table of content
1. [HomeTheather](./HomeTheather.cpp)