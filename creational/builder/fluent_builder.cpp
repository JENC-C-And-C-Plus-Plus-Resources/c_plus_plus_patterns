#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using namespace ::std; 
struct HTMLBuilder;

struct HTMLElement
{
  /* data */
  string name, text;
  vector<HTMLElement> elements;

  const size_t indent_size = 2;

  HTMLElement() {}
  HTMLElement(const string &name, const string &text) : name(name), text(text) {}

  string str(int indent = 0) const
  {
    ostringstream oss;
    string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << endl;

    if (text.size() > 0)
    {
      oss << string(indent_size * (indent + 1), ' ') << text << endl;
    }

    for (const auto &e : elements)
    {
      oss << e.str(indent + 1);
    }

    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }


};


struct HTMLBuilder
{
  HTMLElement root;

  HTMLBuilder(string root_name)
  {
    root.name = root_name;
  }

  HTMLBuilder& add_child(string child_name, string child_text)
  {
    HTMLElement e{child_name,child_text};
    root.elements.emplace_back(e);
    return *this;
  }



  string str() const { return root.str(); }
};


HTMLBuilder build(string root_name)
{
  return HTMLBuilder(root_name);
}

int main()
{
  auto builder = build("ul").add_child("li","hello").add_child("li","world");
  string HTML = builder.str();
  cout << HTML << endl;
  return 0;
}