#ifndef _UTILITY_
#define _UTILITY_

#include "shape.h"

Shape* getShapeById(Shape* shape, std::string id) {
  //platformio-ide-terminal
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return a shape under the input shape tree sturctur that matches the id.
    // throw std::string "Only compound shape can get shape!" when the input shape is not iterable.
    // throw std::string "Expected get shape but shape not found" when no shape found with the given id.
    Iterator* it = shape->createIterator();
    if(it->isDone())
      throw std::string("Only compound shape can get shape!");

    for(it->first(); !it->isDone(); it->next()) {
      Shape* current_shape = it->currentItem();
      try{
        return getShapeById(current_shape, id);
      }
      catch(std::string e) {
        if(current_shape->id() == id)
          return current_shape;
      }
    }

    // No match id
    throw std::string("Expected get shape but shape not found");
}

template <class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter) {
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the shapes under the input shape tree sturctur that match the given filter.
    // throw std::string "Only compound shape can filter shape!" when the input shape is not iterable.
    Iterator* it = shape->createIterator();
    if(it->isDone())
      throw std::string("Only compound shape can filter shape!");

    std::deque<Shape*> deque_shape;
    for(it->first(); !it->isDone(); it->next()) {
      Shape* current_shape = it->currentItem();

      if(filter(current_shape))
        deque_shape.emplace_back(current_shape);

      try{
        std::deque<Shape*> sub_dequpe = filterShape(current_shape, filter);
        while(!sub_dequpe.empty()){
          deque_shape.emplace_back(sub_dequpe[0]);
          sub_dequpe.pop_front();
        }
      }
      catch(std::string e){
        // cout << "filterShape exception : " << e << endl;
      }
    }

    return deque_shape;
}

class AreaFilter {
public:
  AreaFilter(double upperBound, double lowerBound): m_upperBound(upperBound), m_lowerBound(lowerBound) {}
  bool operator() (Shape* shape) const { return m_upperBound > shape->area() && shape->area() > m_lowerBound; }
private:
  double m_upperBound;
  double m_lowerBound;
};

class PerimeterFilter {
public:
  PerimeterFilter(double upperBound, double lowerBound): m_upperBound(upperBound), m_lowerBound(lowerBound) {}
  bool operator() (Shape* shape) const { return m_upperBound > shape->perimeter() && shape->perimeter() > m_lowerBound; }
private:
  double m_upperBound;
  double m_lowerBound;
};

class ColorFilter {
public:
  ColorFilter(std::string color): m_color(color) {}
  bool operator() (Shape* shape) const { return shape->color() == m_color; }
private:
  std::string m_color;
};

class TypeFilter {
public:
  TypeFilter(std::string type): m_type(type) {}
  bool operator() (Shape* shape) const { return shape->type() == m_type; }
private:
  std::string m_type;
};


#endif
