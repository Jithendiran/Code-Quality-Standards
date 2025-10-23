/*
 * Author: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ InterfaceSegregation.cpp -o /tmp/InterfaceSegregation

/*
Interface segregation
Idea of this principle is not create interface which is too large
*/

#include <vector>
#include <iostream>
struct Document;

// This is a multifunctionl document machine, which can do printing, scanning and faxing
struct IMachine
{
    virtual void print(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
};

// This is acceptable
struct MFP : IMachine
{
    void print(Document &doc) override
    {
        std::cout << "Printing..." << std::endl;
    }

    void fax(Document &doc) override
    {
        std::cout << "faxing..." << std::endl;
    }
    void scan(Document &doc) override
    {
        std::cout << "scanning..." << std::endl;
    }
};

// issue is not all the machine are multi functional
// some machine are only do (printing), (scanning), (faxing), (printing, scanning),..

struct single_scanning : public IMachine
{

    /*
     print and fax are not valid for scanning machine
     Since the IMachine has these methods we are forced to override
     now what we can fill up the not supported functionality?
     - Thowing not supported exeception
     - Do nothing
     In both the cases API is exposed, who ever using they may mislead
    */
    void print(Document &doc) override
    {
    }

    void fax(Document &doc) override
    {
    }

    // This is valid
    void scan(Document &doc) override
    {
        std::cout << "scanning..." << std::endl;
    }
};

//-------------------------------------IS

/*
Here the interface are segregated, we no longer forced to implement the unsupported methods
*/

struct IPrinter
{
    virtual void print(Document &doc) = 0;
};

struct IScanner
{
    virtual void scan(Document &doc) = 0;
};

struct IFax
{
    virtual void fax(Document &doc) = 0;
};

struct Scanner : IScanner
{
    IScanner &scanner;
    Scanner(IScanner &scanner) : scanner(scanner) {}
    void scan(Document &doc) override
    {
        scanner.scan(doc);
    }
};

// machine which support noth printing and scanning
struct IPrintandScan : public IPrinter, IScanner
{
};

struct PrinterAndScanner : IPrintandScan
{
    IPrinter &printer;
    IScanner &scanner;

    PrinterAndScanner(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(Document &doc) override
    {
        printer.print(doc);
    }

    void scan(Document &doc) override
    {
        scanner.scan(doc);
    }
};

int main() {
    
}
