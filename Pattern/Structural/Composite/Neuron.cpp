/*
 * Programmer: E.K.Jithendiran
 * Date: 26 Oct 2025
 */
// g++ -o /tmp/Neuron Neuron.cpp

/*
Idea
Neuron is a single entity, Each neuron has in and out connections
Neuron layer is a group of Neuron

* Neuron can connect to other single neuron or layer
* Layer can connect to ther single neuron or layer
*/

#include <cstdio>
#include <vector>
#include <iostream>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
using namespace std;

struct Neuron;

// defining common interface for single neuron and neuron layer
template <typename Self>
struct NeuronCells
{
    template <typename T>
    void connect_to(T &other)
    {
        for (Neuron &from : *static_cast<Self *>(this))
        {
            for (Neuron &to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

// single object
struct Neuron : NeuronCells<Neuron>
{
    vector<Neuron *> in, out;
    unsigned int id;

    Neuron()
    {
        static int id = 1;
        this->id = id++;
    }

    /*
    * why begin and end for single neuron?
    Because we have to access the single neuron and group of neuron (Layer) in the same way, for uniformity to access for loop we are overriding begin and end
    begin will return single neuron address (self address)
    end will return next address which is end of the loop
    */
    Neuron *begin() { return this; }
    Neuron *end() { return this + 1; }

    friend ostream &operator<<(ostream &os, const Neuron &obj)
    {
        for (Neuron *n : obj.in)
        {
            os << n->id << "\t-->\t[" << obj.id << "]" << endl;
        }

        for (Neuron *n : obj.out)
        {
            os << "[" << obj.id << "]\t-->\t" << n->id << endl;
        }
        return os;
    }
};

// composite objects
struct NeuronLayer : vector<Neuron>, NeuronCells<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while (count-- > 0)
            emplace_back(Neuron{});
    }

    friend ostream &operator<<(ostream &os, NeuronLayer &obj)
    {

        for (auto &n : obj)
            os << n;
        return os;
    }
};

void main()
{
    Neuron n1, n2;
    n1.connect_to(n2); // single neuron connetions

    cout << n1 << n2 << endl;

    NeuronLayer l1{5};
    Neuron n3;
    l1.connect_to(n3); // layet to neuron connection

    cout << "Neuron " << n3.id << endl
         << n3 << endl;
    cout << "Layer " << endl
         << l1 << endl;

    NeuronLayer l2{2}, l3{3};
    l2.connect_to(l3); // layer to layer connection
    cout << "Layer l2" << endl
         << l2;
    cout << "Layer l3" << endl
         << l3;

    // Single object and composite object are accessed uniformly through `connect_to`
}