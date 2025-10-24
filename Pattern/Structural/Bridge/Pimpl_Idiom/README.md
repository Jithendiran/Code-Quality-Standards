# Pimpl Idiom (Pointer to Implementation)

The core idea is to move all the private data members and implementation-specific helper methods of a class into a separate, forward-declared class (the "Impl" class) and access it through a pointer within the public interface class

A forward-declared class is a class whose existence is announced to the compiler before its full definition is provided.

```cpp
// example for Forward declaration
// File: MyClassA.h
class ClassB; // Forward declaration of ClassB

class ClassA {
private:
    ClassB* b_ptr; // OK: Can use a pointer to an incomplete type, Forward declaration with in class
public:
    void doSomethingWithB(ClassB& b_ref); // OK: Can use a reference to an incomplete type

    // ClassB b_member; // ERROR: Compiler needs the full size of ClassB for this.
};
// Full definition of ClassA is complete here.
```

## Mechanism and Implementation
1. Interface Class (The Handle):
    * The public class (ClassA) contains only public and protected members and a single private member: a pointer to the implementation class(ClassB* b_ptr).
    * The implementation class (ClassB::Impl) is only forward-declared in the header. Meaning it's data member and member functions are not included in header file, it is only included in cpp file
2. Implementation Class (The Body):
    * The private data members and helper methods of ClassA are defined inside the nested ClassB::Impl class in the source file (.cpp).
3. Bridge
    * All public methods in MyClass simply delegate or "forward" their calls to the corresponding methods on the pImpl pointer.

## Benifit
* It completely hides the implementation details, including private member variables and the types they use, from the header file. The client code only sees the public interface(header file `.h`).

# Contents
1. [Person](./main.cpp)