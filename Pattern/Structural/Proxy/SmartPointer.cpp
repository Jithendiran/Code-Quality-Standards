/*
 * Programmer: E.K.Jithendiran
 * Date: 28 Oct 2025
 */
// g++ -o /tmp/SmartPointer SmartPointer.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

/*
Smart pointer is a proxy
*/

struct BankAccount
{
    virtual ~BankAccount() = default;
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount // checking
{
    explicit CurrentAccount(const int balance)
        : balance(balance)
    {
    }

    void deposit(int amount) override
    {
        balance += amount;
    }

    void withdraw(int amount) override
    {
        if (amount <= balance)
            balance -= amount;
    }

    friend ostream &operator<<(ostream &os, const CurrentAccount &obj)
    {
        return os << "balance: " << obj.balance;
    }

private:
    int balance;
};

int main()
{
    BankAccount *a = new CurrentAccount(123); // This is original obejct
    a->deposit(321);
    delete a;

    // This is a proxy object, it behaves like a original object
    auto b = make_shared<CurrentAccount>(123);

    // b.get is a API of smart pointer, not the original one's. It's a additional capability
    BankAccount *actual = b.get(); // pointer's own operations on a .
    b->deposit(321);               // underlying object's operations are on ->
                                   // note this expression is identical to what's above
    cout << *b << endl;
}