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

template <typename T> struct AndSpecification;

template <typename T> struct Specification {
  virtual ~Specification() = default;
  virtual bool is_satisfied(T *item) const = 0;
};

template <typename T> AndSpecification<T> operator&&
  (const Specification<T>& first, const Specification<T>& second)
{
  return { first, second };
};

template <typename T> struct Filter {
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct ProductFilter : Filter<Product> {
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
  }
};

struct ColorSpecification : Specification<Product> {
  Color color;

  explicit ColorSpecification(const Color color) : color(color) {}

  bool is_satisfied(Product *item) const override {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product> {
  Size size;

  explicit SizeSpecification(const Size size) : size(size) {}

  bool is_satisfied(Product *item) const override {
    return item->size == size;
  }
};

template <typename T> struct AndSpecification : Specification<T> {
  const Specification<T>& first;
  const Specification<T>& second;

  AndSpecification(const Specification<T> &first,const Specification<T> &second ) : first(first), second(second) {}
 
  bool is_satisfied(T *item) const override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

int main()
{

  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const vector<Product *> items{&apple, &tree, &house};

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

  auto and_spec = large_spec && green_spec;
  auto things = filter.filter(items, and_spec);
  for (auto& item: things) {
    cout << item->name << " is large and green; " << endl;
  } 

  return 0;
}