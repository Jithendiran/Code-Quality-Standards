# Proxy

* **Primary Goal**:  To provide an access-controlling layer to a real subject.
Proxy which looks and behavious like an original object

* **Focus**: Controlled Access. The Proxy manages when and how the Real Subject is accessed.

* **Process**: The Proxy has the same interface as the Real Subject, so the Client interacts with the Proxy as if it were the Real Subject.

* **When to Use**: 
    The Proxy design pattern should be used when you need to control access to an object or add a layer of logic before, during, or after accessing it, without changing the object's core class.

**Analogy**

Debit card

* The Real Subject: The Bank Account (holding the money). This is the actual resource you want to access.

* The Proxy: The Debit Card. This is the object you interact with directly. It has the same interface as the real subject in terms of initiating a transaction (e.g., "pay $100").

* Controlled Access:
    - When you swipe the card (interact with the Proxy), the card's system (the Proxy) first performs access control checks (e.g., verifying the PIN or signature, checking if the card is valid, ensuring there are sufficient funds, etc.).
    - Only after these checks pass does the card system (the Proxy) actually allow the transaction to proceed and interact with the Bank Account (the Real Subject) to deduct the money. 

The card lets you access your money, but it controls when and how that access happens. You don't interact directly with the vault or the bank's ledger every time you buy something; you use the Proxy.

## Table of Content
1. [SmartPointer](./SmartPointer.cpp)
2. [Property](./Property.cpp)
3. [Virtual](./Virtual.cpp)
4. [Communication](./Communication.cpp)