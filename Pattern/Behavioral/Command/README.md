# Prototype

* **Primary Goal**: 

* **Focus**:

* **Process**: 

* **When to Use**: 


* **Analogy**
A waiter in a restaurant. The Client (Diner) decides what they want. They write their order on a Command object (the Order Slip). The Invoker (Waiter) takes the slip and hands it to the Receiver (Chef). The Waiter doesn't know how the food is made, just that the Chef can fulfill the request on the slip. The Order Slip decouples the Diner from the Chef

## Command and Query

### Command
Command design pattern asking for an action or change, It modify the value and it does't return a value
Example: poperty setter, it will set the new value and it doesn't return any value
obj.setProp("value)

### Query
Query design pattern asking for information, it returns the value and doesn't modify
Example: property getter, it will get the property value and it doesn't alter the property value
a = obj.getProp()

### Command query separation
Separate the system into two component one for query and other for command

## Table of content
1. [Command](./Command.cpp)