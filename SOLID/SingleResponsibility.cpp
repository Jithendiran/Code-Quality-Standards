/*
* Author: E.K.Jithendiran
* Date: 23 Oct 2025
*/
// g++ SingleResponsibility.cpp -o /tmp/journal_app -lboost_system
/*
Single Responsibility Principle (SRP)

A class should have **only one reason to change**, meaning it should only be responsible for one specific piece of functionality or area of the system.
It should not take on unrelated responsibilities.

Real world example:
A programmer's **primary responsibility** is programming and solving related technical problems. 
While they can decompose large problems into smaller, manageable ones, their class/role shouldn't include tasks like making coffee/tea, as that is an **unrelated concern**.
*/

/*
Journal Class Responsibilities
- The Journal class is responsible for managing its **data structure** (title and entries).
- Its core methods are to **add, edit, and modify** entries.

Why is saving and loading *not* the responsibility of the Journal class?
This adheres to the **Single Responsibility Principle** and the **Separation of Concerns** principle.

The problem with putting persistence (saving/loading) code inside the Journal class is:
1.  **Violation of SRP:** The class would have two reasons to change: if the journal logic changes, *or* if the persistence mechanism changes (e.g., switching from file saving to a database or a cloud service).
2.  **Increased Coupling:** Changes to the persistence code would force modifications to the Journal class, and potentially many other classes using it, leading to a less stable system.
3.  **Lack of Flexibility:** Changing the storage type (e.g., from `file` to `database`) would require modifying the Journal class itself, which is not ideal.

Separation of Concerns:
- **Journal** should exclusively handle **journal domain logic** (title, add, edit, modify entries).
- **Persistence** (saving and loading) should be delegated to a **separate class/module** (like `PersistenceManager`), making the system more robust and flexible.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
using namespace std;

struct Journal
{
  string title;
  vector<string> entries;

  explicit Journal(const string& title)
    : title{title}
  {
  }

  void add(const string& entry);

  // persistence is a separate concern
  void save(const string& filename);
};

void Journal::add(const string& entry)
{
  static int count = 1;
  entries.push_back(boost::lexical_cast<string>(count++)
    + ": " + entry);
}

// This is not recommanded
void Journal::save(const string& filename)
{
  ofstream ofs(filename); // file creation and opening
  for (auto& s : entries)
    ofs << s << endl; // writing the content to file
} // <-- 'ofs' object goes out of scope here

// ofstream object is closed automatically when the ofs object goes out of scope.

struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto& s : j.entries)
      ofs << s << endl;
  }
};

int main()
{
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  //journal.save("diary.txt");

  PersistenceManager pm;
  pm.save(journal, "/tmp/diary.txt");
}

