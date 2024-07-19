#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using namespace::std;

int main() {
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    cout << output << endl;

    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (auto w: words){
        oss << " <li>" << w << "</li>";
    }
    oss << "</ul>";
    cout << oss.str() << endl; 

    return 0;
} 