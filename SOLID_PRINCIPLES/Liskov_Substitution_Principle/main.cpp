#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Rectangle
{
protected:
  int width, height;

public:
  Rectangle(int width, int height) : width(width), height(height) {}

  int getWidth() const
  {
    return width;
  }
  virtual void setWidth(int width)
  {
    Rectangle::width = width;
  }
  int getHeigth() const
  {
    return height;
  }
  virtual void setHeight(int height)
  {
    Rectangle::height = height;
  }

  int area() const { return width * height; }
};

class Square : public Rectangle 
{
  public:
    Square(int size): Rectangle(size, size){}

    void setWidth(int width) override {
      this->width = this->height = width;
    }

    void setHeight(int height) override {
      this->width = this->height = height;
    }
};


void process(Rectangle& r) {
  int w = r.getWidth();
  r.setWidth(10);

  cout << " expected area = " << (w*10)
       << " ,got " << r.area() << endl; 
}

int main()
{

  // This code demostrates what happens when the Liskov principle is not applied.
  Rectangle rect{3,10};
  process(rect);

  Square sq{5};
  process(sq);
  return 0;
}