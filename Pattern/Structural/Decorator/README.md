# Decorator

* **Primary Goal**: To extend or modify the behavior of an individual object at runtime.

* **Focus**: Responsibility Extension. It focuses on adding new capabilities or features to an existing object.

* **Process**: Wrapping and Delegation. It wraps the original object and delegates calls to it, while also executing the new functionality it adds.

* **When to Use**: When you need to add responsibilities to individual objects in a flexible way, or when subclassing is impractical, whithout modifying the core object

**Analogy**
An analogy is customizing a video game character with armor and items.

The core Character is the base object. You can then decorate it with a Helmet, which adds a defense bonus. You can decorate that with Body Armor, which adds more defense and possibly a strength bonus. Finally, you can decorate that with a Magic Sword, which adds an attack bonus.

The Decorator pattern adheres to the **Open/Closed Principle**

## Table of content
1. [Dynamic](./Dynamic.cpp)
2. [Static](./Static.cpp)
3. [Functional](./Functional.cpp)