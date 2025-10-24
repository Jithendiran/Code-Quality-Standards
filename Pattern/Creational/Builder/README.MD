# Builders

* **Primary Goal**: To construct a single, complex object step-by-step, often with many optional configurations.

* **Process**: Multi-step creation. You call multiple methods to set different properties, and a final build() method returns the object.The product isn't available until the final step

* **Focus**: How to create the object. (The object's construction process.)

* **When to Use**: When an object has many possible parameters or a complex internal structure, and you want to ensure it's built correctly.

**Analogy**
Ordering a custom sandwich : You specify the bread, meat, cheese, toppings, and sauces in separate steps before it's finished.

## Table of content
1. [Builder](./Builder.cpp)
2. [Facets](./Facets.cpp)