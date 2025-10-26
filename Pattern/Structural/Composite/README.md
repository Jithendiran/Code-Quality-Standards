# Composite

* **Primary Goal**: To enable clients to treat individual objects and compositions of objects uniformly.

* **Focus**: It establishes a common interface for both the simple elements and the container elements that hold them.

* **Process**: Uniformity

* **When to Use**: When you have data or objects that can be grouped hierarchically, and you want to perform operations on both the simple components and the complex containers in the same way, avoiding a proliferation of conditional statements

**Analogy**
A computer file system (Directories and Files). The client code can call an operation like display_size() on either an individual File (a Leaf) or a Directory (a Composite), and the operation works seamlessly. The Directory recursively calculates the total size of everything inside it (including other Directories).


## Table of Content
1. [Geometry](./Geomentry.cpp)
2. [Neuron](./Neuron.cpp)
3. [ArrayBacked](./ArrayBacked.cpp)