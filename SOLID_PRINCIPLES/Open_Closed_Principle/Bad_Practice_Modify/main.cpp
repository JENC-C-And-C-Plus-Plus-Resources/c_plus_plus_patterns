#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Color { red, green, blue };
enum class Size { small, medium, large};

struct Product {
    string name;
    Color color;
    Size size;
};

struct ProductFilter {
    vector<Product*> by_color(vector<Product*> items, Color color) {
        vector<Product*> result;
        for (auto& item : items){
            if(item->color == color) {
                result.push_back(item);
            }
        }
        return result;
    }

    vector<Product*> by_size(vector<Product*> items, Size size) {
        vector<Product*> result;
        for (auto& item : items){
            if(item->size == size) {
                result.push_back(item);
            }
        }
        return result;
    }

    vector<Product*> by_size_and_color(vector<Product*> items, Color color, Size size) {
        vector<Product*> result;
        for (auto& item : items){
            if(item->size == size && item->color == color) {
                result.push_back(item);
            }
        }
        return result;
    }
};


int main() {

    Product apple {"Apple", Color::green, Size::small};
    Product tree  {"Tree", Color::green, Size::large};
    Product house {"House", Color::blue, Size::large};

    vector<Product*> items { &apple, &tree, &house };

    ProductFilter pf;
    auto green_things = pf.by_color(items, Color::green);
    for (auto& green_item: green_things) {
        cout << green_item->name << " is green; " << endl;
    }

    auto large_things = pf.by_size(items, Size::large);
    for (auto& large_item: large_things) {
        cout << large_item->name << " is large; " << endl;
    } 

    auto small_and_green_things = pf.by_size_and_color(items, Color::green, Size::small);
    for (auto& item: small_and_green_things) {
        cout << item->name << " is small and green; " << endl;
    } 

    return 0;
}