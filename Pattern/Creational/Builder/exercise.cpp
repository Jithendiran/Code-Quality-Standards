// g++ exercise.cpp -o /tmp/exercise
#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

struct Field
{
    string name, type;
};

class CodeBuilder
{
private:
    string class_name;
    vector<Field> fields;
    const int indent_size = 2;

    // Helper function for indentation
    string indentation(int level) const
    {
        return string(level * indent_size, ' ');
    }

public:
    CodeBuilder(const string &class_name) : class_name(class_name)
    {
    }

    CodeBuilder &add_field(const string &name, const string &type)
    {
        fields.emplace_back(Field{name, type});
        return *this;
    }

    friend ostream &operator<<(ostream &os, const CodeBuilder &obj)
    {
        // 1. Class definition line
        os << "class " << obj.class_name << "\n";
        os << "{\n";

        // 2. Fields (2-space indentation)
        for (const auto &f : obj.fields)
        {
            // Two-space indentation
            os << obj.indentation(1) << f.type << " " << f.name << ";\n";
        }

        // 3. Closing brace and semicolon
        os << "};\n";

        return os;
    }
};

int main()
{
    // Build the code structure using the fluent interface
    auto cb = CodeBuilder{"Person"}
                  .add_field("name", "string")
                  .add_field("age", "int");

    // Output the generated code
    cout << cb;

    // Expected Output:
    // class Person
    // {
    //   string name;
    //   int age;
    // };

    return 0;
}