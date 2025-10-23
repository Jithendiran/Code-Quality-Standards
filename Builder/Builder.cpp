/*
 * Author: E.K.Jithendiran
 * Date: 23 Oct 2025
 */
// g++ Builder.cpp -o /tmp/Builder

/*
Builder
The Builder Pattern is designed to separate the construction of a complex object from its representation, allowing the same construction process to create different representations.

It is particularly useful when an object has many parameters (often optional) and its construction involves multiple steps or requires the resulting object to be immutable (read-only) once built.

*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

struct HtmlBuilder;

// This is the actual class
struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements; // child elemnts
    const size_t indent_size = 2;

    // This has different ways to create object
    HtmlElement() {}

    HtmlElement(const string &name, const string &text) : name(name), text(text) {}

    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');    // printing spaces, for better look
        oss << i << "<" << name << ">" << endl; // tag name formation
        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto &e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    // This is used to build the object from the main class
    static unique_ptr<HtmlBuilder> build(string root_name)
    {
        return make_unique<HtmlBuilder>(root_name);
    }
};

// this is responsible only for creating the HtmlElement
struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(string root_name)
    {
        root.name = root_name;
    }

    // returning HtmlBuilder allows for chain of creation
    HtmlBuilder &add_child(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    // pointer based
    HtmlBuilder *add_child_2(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }

    string str() { return root.str(); }

    // This is used to convert HtmlBuilder to HtmlElement
    operator HtmlElement() const { return root; }
};

//---------
// data class
struct Tag
{
    std::string name; // tag
    std::string text; // content/inner text
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;
    // attribute is a key value pair of vector

    // for printing
    friend std::ostream &operator<<(std::ostream &os, const Tag &tag)
    {
        os << "<" << tag.name;

        for (const auto &att : tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>" << std::endl;
        }
        else
        {
            os << ">" << std::endl;

            if (tag.text.length())
                os << tag.text << std::endl;

            for (const auto &child : tag.children)
                os << child;

            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

    // different constructors
protected:
    Tag(const std::string &name, const std::string &text)
        : name{name},
          text{text}
    {
        // <p>aabb</p>
    }

    Tag(const std::string &name, const std::vector<Tag> &children)
        : name{name},
          children{children}
    {
        //<ul><li>aa</li><ul>
    }
};

// builders class
// para tag
struct P : Tag
{
    // different constructord
    explicit P(const std::string &text)
        : Tag{"p", text}
    {
        //<p>aa</p>
    }
    // initializer_list allows list of child tags 
    P(std::initializer_list<Tag> children)
        : Tag("p", children)
    {
        // <p><img src="a"/><img src="b"/></p>
        // p{img{"a"},img{"b"}}
    }
};

struct IMG : Tag
{
    explicit IMG(const std::string &url)
        : Tag{"img", ""}
    {
        attributes.emplace_back(make_pair("src", url));
    }
};

int main()
{
    // --------------------------------------without builder
    // generate a html tag with content
    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p>", text);

    // <ul><li>hello</li><li>world</li></ul>
    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
        oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    printf(oss.str().c_str());

    //----------------------------------------

    // easier
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    // .add_child("li", "hello").add_child("li", "world"); // this is called fluent builder
    cout << builder.str() << endl;

    auto builder2 = HtmlElement::build("ul")
                        ->add_child_2("li", "hello")
                        ->add_child_2("li", "world");
    cout << builder2 << endl;

    //----------------------------------

    std::cout <<

        P{
            IMG{"http://pokemon.com/pikachu.png"}
        }

              << std::endl;
    return 0;
}