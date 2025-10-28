# Flyweight

* **Primary Goal**: To minimize memory usage by sharing as much data as possible among a large number of fine-grained objects.

* **Focus**:  Optimization and Efficiency. It focuses on reducing the memory footprint when dealing with massive collections of similar objects.

* **Process**: Separation of State and Factory Management. It separates an object's state into two parts: Intrinsic (shared) and Extrinsic (unique), and uses a Factory to manage and reuse the shared objects.

* **When to Use**: 
    * When most of an object's information is unique and changes all the time.
    * When memory consumption is a significant performance issue.

**Analogy**

Imagine you are running a massive elementary school art class with 500 students, and every student needs to draw a picture using a set of standard colors.

The Problem (No Flyweight)
* You buy 500 complete boxes of 24 crayons.
* Each student gets their own entire box.
* The memory-intensive part is the actual, physical crayon stick itself (the wax and pigment).

Result: You have 500 individual Red crayons, 500 individual Blue crayons, etc. You are duplicating 24 sets of the same color information (intrinsic/shared state) 500 times. This is hugely expensive (memory-intensive).

The Solution (Using Flyweight):

You realize that the physical crayon (the Intrinsic/shared State) can be shared, while the act of drawing (the Extrinsic/unique State) is unique to each student.

1. Intrinsic/shared State (The Flyweight): The Crayon Sticks.

    - You buy only one master set of 24 crayon sticks (one Red, one Blue, one Yellow, etc.). This is your small, shared pool of Flyweight objects.
    - The color information (Red pigment recipe, Blue pigment recipe) is stored only once inside each shared crayon.

2. Extrinsic/unique State (The Context): The Student and the Drawing.

    - The unique, unshareable information is who is drawing, where they are drawing (position on the paper), and what pressure they use.
    - This unique information is stored separately for each student.

3. The Factory (The Teacher):

    - The teacher manages the small box of 24 shared crayons.
    - When a student needs to color a spot red, the student says, "I need the Red crayon."
    - The teacher retrieves the single shared Red Crayon object and hands it to the student.

Conclusion: Instead of storing 12,000 crayons (500 students × 24 colors), you only store 24 shared crayons (the intrinsic/shared state) and the unique drawing context (extrinsic/unique state) for each of the 500 students. This dramatically reduces the physical "memory" required.

## Table of content
1. [Handmade](./HandMade.cpp)
2. [TextFormat](./TextFormat.cpp)