#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal {
    string title;
    vector<string> entries;
    Journal(const string& title): title(title) {}

    void add_entry(const string& entry) {
        static int count = 1;
        
        string formatted_entry = lexical_cast<string>(count++) + ": " + entry;
        cout << formatted_entry << endl;
        entries.push_back(formatted_entry);
    }

};

struct PersistenceManager {
    static void save(const Journal& journal, const string& filename) {
        ofstream ofs(filename);
        for (auto&entry: journal.entries) {
            ofs << entry << endl;
        }
        ofs.close();
    }
};

int main() {
    Journal journal {"Dear Dairy"};
    journal.add_entry("Note 1");
    journal.add_entry("Note 2");
    journal.add_entry("Note 3");
    journal.add_entry("Note 4");


    Journal journal2 {"Dear Dairy"};
    journal2.add_entry("Note 1");
    journal2.add_entry("Note 2");
    journal2.add_entry("Note 3");
    journal2.add_entry("Note 4");

    PersistenceManager pm;
    pm.save(journal, "journal.txt");
    pm.save(journal2, "journal2.txt");

    getchar();
    return 0;
}
