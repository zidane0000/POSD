//include basic C/C++ library
#include <iostream>
#include <math.h>
#include <string>
#include <exception>
#include <regex>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <list>

#ifndef _SHAPE_
#define _SHAPE_

#include "iterator.h"
#include "visitor.h"

using namespace std;

class Shape {
public:
  Shape(std::string id);
  Shape(std::string id, std::string color);
  std::string id() const; // return id of shape
  std::string color() const; // return color of shape.
  void setColor(std::string color);
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
  virtual std::string type() const = 0;
  virtual void addShape(Shape *shape); // throw std::string "Only compound shape can add shape!"
  virtual void deleteShapeById(std::string id); // throw std::string "Only compound shape can delete shape!"
  virtual Shape* getShapeById(std::string id) const; // throw std::string "Only compound shape can get shape!"
  virtual Iterator* createIterator() const;
  virtual void accept(Visitor* visitor) = 0;
  virtual ~Shape();

private:
  std::string m_id;
  std::string m_color;
};

#endif
