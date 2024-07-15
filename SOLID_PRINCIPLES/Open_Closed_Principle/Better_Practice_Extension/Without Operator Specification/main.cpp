#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Color
{
  red,
  green,
  blue
};
enum class Size
{
  small,
  medium,
  large
};

struct Product
{
  string name;
  Color color;
  Size size;
};

template <typename T>
struct Specification
{
  virtual bool is_satisfied(T *item) = 0;
};

template <typename T>
struct Filter
{
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

template <typename T>
struct AndSpecification: Specification<T>
{
  Specification<T>& first;
  Specification<T>& second;

  AndSpecification(Specification<T> &first, Specification<T> &second ) : first(first), second(second) {}

  bool is_satisfied(T *item) override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

struct ProductFilter : Filter<Product>
{
  vector<Product *> filter(vector<Product *> items, Specification<Product> &spec) override
  {
    vector<Product *> result;
    for (auto &item : items)
    {
      if (spec.is_satisfied(item))
      {
        result.push_back(item);
      }
    }
    return result;
  };
};

struct ColorSpecification : Specification<Product> {
  Color color;

  explicit ColorSpecification(const Color color) : color(color) {}

  bool is_satisfied(Product *item) override {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product> {
  Size size;

  explicit SizeSpecification(const Size size) : size(size) {}

  bool is_satisfied(Product *item) override {
    return item->size == size;
  }
};



int main()
{

  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  vector<Product *> items{&apple, &tree, &house};

  ColorSpecification green_spec {Color::green};
  SizeSpecification large_spec(Size::large);

  ProductFilter filter;

  auto green_things = filter.filter(items, green_spec);

  for (auto& item: green_things) {
    cout << item->name << " is green; " << endl;
  } 

  auto large_things = filter.filter(items, large_spec);
  for (auto& item: large_things) {
    cout << item->name << " is large; " << endl;
  } 

  SizeSpecification small_spec(Size::small);
  AndSpecification small_and_green (small_spec, green_spec);

  auto things = filter.filter(items, small_and_green);
  for (auto& item: things) {
    cout << item->name << " is small and green; " << endl;
  } 

  return 0;
}