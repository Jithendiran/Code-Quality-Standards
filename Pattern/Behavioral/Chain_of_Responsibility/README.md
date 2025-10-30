# Chain of Responsibility

A chain of components who all get a chance to process a command or a query, optionally haveing default processing implementation and an ability to terminate the process chain

* **Primary Goal**: 
To avoid coupling the sender of a request to its receiver by allowing multiple objects a chance to handle the request. A request is passed along a sequential chain of processing objects until one handles it.
example : network layers

* **Focus**:  How to process a request:  
 by asking a chain of handlers to process it sequentially. It focuses on the decoupling between the request issuer (Client) and the ultimate request processor (Handler).

* **Process**:  Chaining:  
 The Client submits a request to the first object (handler) in a pre-linked chain. Each handler contains logic to decide whether it processes the request, or forwards it to its successor (the next object) in the chain or Reject the process

* **When to Use**: 
    When you want to execute a sequence of operations (e.g., filters, validations, or permissions checks) on a request in a specific, yet configurable, order.

* **Analogy**
Corporate Approval Flow
An Employee (Client) submits a Request (e.g., for a budget increase).
1. The request first goes to the Senior Handler. If they can approve it (e.g., a small amount), the chain stops.
2. If the request is too large, the Senior passes it to their successor, the Manager Handler.
3. If the Manager's authority limit is exceeded, they pass it to the CEO Handler. The employee doesn't need to know the approval limits; they just send the request to the first person in the chain.

## Table of content
1. [Pointers](./Pointers.cpp)
2. [Broker](./Broker.cpp)