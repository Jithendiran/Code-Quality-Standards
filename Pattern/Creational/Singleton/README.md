# Prototype

* **Primary Goal**: To enforce that a class has only one object (instance) throughout the entire application lifecycle.

* **Focus**: Uniqueness and Global Access. The focus is on controlling the creation process so that no one can accidentally create a second object.

* **Process**: Private Constructor and Static Access.

* **When to Use**: 
   1. When you need a single object to coordinate actions across the system (e.g., a Logger or a Configuration Manager). 
   2. When you need to manage a shared, unique resource, such as a Database Connection Pool or a Thread Pool.

## Table of content
1. [Singleton](./Singleton.cpp)