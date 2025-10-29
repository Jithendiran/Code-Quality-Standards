/*
 * Programmer: E.K.Jithendiran
 * Date: 28 Oct 2025
 */
// g++ -o /tmp/Communication Communication.cpp

/*
Idea
It is about relocating the some piece of functionality from local to remote

Its job is to: 
    * Package the client's request parameters (marshalling). 
    * Send the request over the network. 
    * Receive the response from the remote object. 
    * Unpack the response (unmarshalling) and return the result to the client.

The main goal is to hide the complexity of network communication (like serialization, sockets, and network protocols) from the client, making the remote object appear as if it were a local object.
*/

// 1. Subject Interface
// This defines the common interface for both the real remote service and its local proxy.

#include <thread>
#include <string>
#include <chrono>
#include <iostream>

using namespace std;

class BankAccount
{
public:
    virtual ~BankAccount() = default;
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
};

// Real object
// This is the actual object with the business logic, residing on a remote machine.
// 2. Real Subject (The object on a remote server)
class RealBankAccount : public BankAccount
{
private:
    double balance_ = 0.0;

public:
    RealBankAccount(double initialBalance) : balance_(initialBalance) {
        std::cout << "Real Account: Initialized on the remote server." << std::endl;
    }


    void deposit(double amount) override {
        balance_ += amount;
        std::cout << "Real Account: Deposited $" << amount << ". New balance: $" << balance_ << std::endl;
    }

    void withdraw(double amount) override {
        if (balance_ >= amount) {
            balance_ -= amount;
            std::cout << "Real Account: Withdrew $" << amount << ". New balance: $" << balance_ << std::endl;
        } else {
            std::cout << "Real Account: Insufficient funds for $" << amount << " withdrawal." << std::endl;
        }
    }

    double getBalance() const override {
        std::cout << "Real Account: Sending balance request result across the network." << std::endl;
        return balance_;
    }
};

// 3. Remote Proxy (The communication handler)
// local code, acts as a proxy
class RemoteBankAccountProxy : public BankAccount
{
private:
    RealBankAccount* realAccount_; // Pointer to the real remote service (or a communication stub)

    // Simulate network latency and request packaging
    void simulateNetworkCall(const std::string& action) const {
        std::cout << "\n[PROXY] Marshalling/Sending request for '" << action << "' over the network..." << std::endl;
        // In a real application, this would involve sockets, serialization, etc.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate delay
        std::cout << "[PROXY] Request sent. Waiting for response..." << std::endl;
    }
    
    // Simulate network response unpacking
    void simulateNetworkResponse() const {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate delay
        std::cout << "[PROXY] Received and unmarshalled response." << std::endl;
    }

public:
    // In real world we cannot pass RealBankAccount object instead communication happen through netwoking or something
    RemoteBankAccountProxy(RealBankAccount* realAcc) : realAccount_(realAcc) {
        // Assume the connection details (IP/Port) for the remote service are configured here
    }

    void deposit(double amount) override {
        simulateNetworkCall("deposit");
        realAccount_->deposit(amount); // Delegate to the actual remote object
        // It might be POST /deposit HTTP/1.1\n\n{"amount": 1000.0}, not remote's deposite directly, here for simplicity we use it directly
        simulateNetworkResponse();

        /*
        How it actually happen?
        The client code, unaware of the network, calls the method on the local Proxy object using the common interface (BankAccount*).
        1. Client Code: account->deposit(500.0);

        2. The deposit method inside the RemoteBankAccountProxy (the local object) is executed. Its job is not to update the balance, but to prepare the remote call.
            - The Proxy determines the method name (deposit) and the parameters (500.0).
            - It then serializes (or marshals) this information, converting the C++ method call and its types into a structured byte stream (like a JSON payload or a Protocol Buffer message).
        3. Network Transmission (The Jump)
        4. Remote Server Stub (The Skeleton) Unmarshalling
            On the remote server, there is a listening component (often called a Skeleton or Server Stub) that receives the incoming byte stream.
            
            The Skeleton unmarshals (deserializes) the byte stream back into the original method name (deposit) and the C++ data type (double amount = 500.0).
        5. The Skeleton now has the original method call and parameters. It creates the final C++ call on the actual remote business object, the RealBankAccount.
        */
    }

    void withdraw(double amount) override {
        simulateNetworkCall("withdraw");
        realAccount_->withdraw(amount); // Delegate to the actual remote object
        simulateNetworkResponse();
    }

    double getBalance() const override {
        simulateNetworkCall("getBalance");
        double balance = realAccount_->getBalance(); // Delegate
        simulateNetworkResponse();
        return balance;
    }
};

// ... (Bank Account class definitions from above) ...

void client_operation(BankAccount& account)
{
    std::cout << "--- Client starts transaction ---" << std::endl;

    // Client calls methods without knowing they are being sent over a network!
    account.deposit(500.0);

    account.withdraw(150.0);

    double final_balance = account.getBalance();
    std::cout << "Client: Final observed balance is $" << final_balance << std::endl;

    std::cout << "--- Client transaction complete ---" << std::endl;
}

int main()
{
    // The Real Subject (Simulated as being local for this simple example)
    RealBankAccount realService(1000.0); 

    std::cout << "\n============================================\n" << std::endl;

    // The Proxy that will handle communication with the Real Subject
    RemoteBankAccountProxy communicationProxy(&realService);

    // The client code uses the proxy through the common interface
    client_operation(communicationProxy);

    return 0;
}