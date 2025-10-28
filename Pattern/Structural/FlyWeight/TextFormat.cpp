/*
 * Programmer: E.K.Jithendiran
 * Date: 27 Oct 2025
 */
// g++ -o /tmp/TextFormat TextFormat.cpp

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
using namespace std;

// less-flexible, non-Flyweight approach
class FormattedText
{
    string plain_text;
    // size of caps is same as plain_text: lot's wasted memory
    bool *caps;

public:
    explicit FormattedText(const string &plainText)
        : plain_text{plainText}
    {
        caps = new bool[plainText.length()];
    }
    ~FormattedText()
    {
        delete[] caps;
    }
    void capitalize(int start, int end)
    {
        for (int i = start; i <= end; ++i)
            caps[i] = true;
    }

    friend std::ostream &operator<<(std::ostream &os, const FormattedText &obj)
    {
        string s;
        for (int i = 0; i < obj.plain_text.length(); ++i)
        {
            char c = obj.plain_text[i];
            s += (obj.caps[i] ? toupper(c) : c);
        }
        return os << s;
    }
};

// Flexible approach that hints at the Flyweight pattern's idea of separating intrinsic data (the plain text) from extrinsic data (the formatting ranges).

/*
Idea is to store only the formated index in seperate vector
*/
class BetterFormattedText
{
public:

    // inner struct
    // This is only for formatted text
    struct TextRange
    {
        int start, end;
        bool capitalize, bold, italic;

        bool covers(int position) const
        {
            return position >= start && position <= end;
        }
    };

    TextRange &get_range(int start, int end)
    {
        // Push the text range
        formatting.emplace_back(TextRange{start, end});
        // return 1st element of vector
        return *formatting.rbegin();
    }

    explicit BetterFormattedText(const string &plainText)
        : plain_text{plainText}
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const BetterFormattedText &obj)
    {
        string s;
        for (size_t i = 0; i < obj.plain_text.length(); i++)
        {
            auto c = obj.plain_text[i];

            // loop the format vector
            for (const auto &rng : obj.formatting)
            {
                if (rng.covers(i) && rng.capitalize)
                    c = toupper(c);
                s += c;
            }
        }
        return os << s;
    }

private:
    string plain_text;
    vector<TextRange> formatting; 
};

int main(int argc, char *argv[])
{
    FormattedText ft("This is a brave new world");
    ft.capitalize(10, 15);
    cout << ft << endl;

    BetterFormattedText bft("This is a brave new world");
    bft.get_range(10, 15).capitalize = true;
    cout << bft << endl;
}
