# Prototype

* **Primary Goal**: To create new objects by cloning an existing instance (the prototype) instead of using the new keyword, thereby avoiding the complexity and overhead of instantiation.

* **Focus**: How to create an object: by asking an object to clone itself. It focuses on the object's state that is being copied.

* **Process**: Cloning. A partially or fully initialized object (the prototype) is registered. When a new object is required, the client asks the prototype to execute a clone() or copy() method.

* **When to Use**: 
    1. When object creation is expensive (e.g., loading from a database or file system). 
    2. When you have an object that needs to be created with many initial configurations that can be set once and then cloned for reuse.

* **Analogy**
Photocopying or 3D Printing. You don't build a new paper from scratch for every copy; you take one original document (the prototype) and quickly reproduce it. The original object already has the complex data/structure initialized, and cloning is much faster than running the full constructor process again.

>[!NOTE]  
>- Required deep copy of the object instead of shallow copy
>- It can be partially or fully initilized object that you copy

## Problem

What is the problem without factory pattern?

[Problem](./Problem.cpp)

## Table of contents
1. [Prototype](./Prototype.cpp)
