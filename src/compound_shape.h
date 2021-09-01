#ifndef _COMPUND_SHAPE_
#define _COMPUND_SHAPE_

#include "shape.h"
#include "shape_iterator.h"
#include "visitor.h"

class CompoundShape : public Shape {
public:
  CompoundShape(std::string id, std::list<Shape*> shapes): Shape(id, "transparent") {
    // The default color of compound shape should be "transparent".
    // When there's no shape contain in the compound shape,
    // should throw std::string "This is not a compound shape!"
    /*if(shapes.size() == 0)
      throw std::string("This is not a compound shape!");
    else {
      // m_id = id;
      // m_color = "transparent";
      m_shapes = shapes;
    }*/
    m_shapes = shapes;
  }

  Iterator* createIterator() const {
    return new ShapeIterator<std::list<Shape*>::const_iterator>(m_shapes.begin(), m_shapes.end());
  }

  double area() const {
    // return sum of all containing shapes area.
    double sum_area = 0.0;
    if(!m_shapes.empty())
      for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
        sum_area += (*itr)->area();
    return sum_area;
  }

  double perimeter() const {
    // return sum of all containing shapes perimeter.
    double sum_perimeter = 0.0;
    if(!m_shapes.empty())
      for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
        sum_perimeter += (*itr)->perimeter();
    return sum_perimeter;
  }

  std::string info() const {
    // return list of all containing shapes info with wrapped of "CompoundShape {}".
    // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
    std::string sum_info = "Compound Shape {";
    if(!m_shapes.empty())
      for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
        sum_info = sum_info + (*itr)->info() + ", ";

    if(sum_info[sum_info.size()-2] == ',' && sum_info[sum_info.size()-1] == ' ')
        sum_info = sum_info.substr(0, sum_info.size() - 2);

    sum_info+= "}";
    return sum_info;
  }

  void addShape(Shape* shape) {
    // add shape into compound shape.
    m_shapes.push_back(shape);
  }

  void deleteShapeById(std::string id) {
    // search and delete a shape through id,
    // search all the containing shapes and the tree structure below,
    // if no match of id, throw std::string "Expected delete shape but shape not found"
    for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
      try {
        (*itr)->deleteShapeById(id);
        return;
      }
      catch(std::string e) {
        if((*itr)->id() == id) {
          m_shapes.erase(itr);
          return;
        }
      }
    }

    // No match id
    throw std::string("Expected delete shape but shape not found");
  }

  Shape* getShapeById(std::string id) const {
    // search and return a shape through id,
    // search all the containing shapes and the tree structure below,
    // if no match of id, throw std::string "Expected get shape but shape not found"
    for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
      try{
        return (*itr)->getShapeById(id);
      }
      catch(std::string e) {
        if((*itr)->id() == id)
          return (*itr);
      }
    }

    // No match id
    throw std::string("Expected get shape but shape not found");
  }

  std::string type() const {
    return "Compound Shape";
  }

  void accept(Visitor* visitor) {
    visitor->visit(this);
  }

  std::list<Shape*> getShapes() {
    return m_shapes;
  }

private:
  std::list<Shape*> m_shapes;
};

// class CompoundShape : public Shape{
// public:
//   CompoundShape(std::string id, std::list<Shape*>* shapes): Shape(id, "transparent") {
//     // The default color of compound shape should be "transparent".
//     // When there's no shape contain in the compound shape,
//     // should throw std::string "This is not a compound shape!"
//     if(shapes->size() == 0)
//       throw std::string("This is not a compound shape!");
//     else {
//       // m_id = id;
//       // m_color = "transparent";
//       m_shapes = shapes;
//     }
//   }
//
//   Iterator* createIterator() const {
//     return new ShapeIterator<std::list<Shape *>::iterator>(m_shapes.begin(), m_shapes.end());
//   }
//
//   double area() const {
//     // return sum of all containing shapes area.
//     double sum_area = 0.0;
//     if(m_shapes)
//       for(std::list<Shape*>::iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
//         sum_area += (*itr)->area();
//     return sum_area;
//   }
//
//   double perimeter() const {
//     // return sum of all containing shapes perimeter.
//     double sum_perimeter = 0.0;
//     if(m_shapes)
//       for(std::list<Shape*>::iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
//         sum_perimeter += (*itr)->perimeter();
//     return sum_perimeter;
//   }
//
//   std::string info() const {
//     // return list of all containing shapes info with wrapped of "CompoundShape {}".
//     // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
//     std::string sum_info = "Compound Shape {";
//     if(m_shapes)
//       for(std::list<Shape*>::iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++)
//         sum_info = sum_info + (*itr)->info() + ", ";
//     sum_info = sum_info.substr(0, sum_info.size() - 2);
//     sum_info+= "}";
//     return sum_info;
//   }
//
//   void addShape(Shape* shape) {
//     // add shape into compound shape.
//     m_shapes.push_back(shape);
//   }
//
//   void deleteShapeById(std::string id) {
//     // search and delete a shape through id,
//     // search all the containing shapes and the tree structure below,
//     // if no match of id, throw std::string "Expected delete shape but shape not found"
//     for(std::list<Shape*>::iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
//       try {
//         (*itr)->deleteShapeById(id);
//         return;
//       }
//       catch(std::string e) {
//         if((*itr)->id() == id) {
//           m_shapes.erase(itr);
//           return;
//         }
//       }
//     }
//
//     // No match id
//     throw std::string("Expected delete shape but shape not found");
//   }
//
//   Shape* getShapeById(std::string id) const {
//     // search and return a shape through id,
//     // search all the containing shapes and the tree structure below,
//     // if no match of id, throw std::string "Expected get shape but shape not found"
//     for(std::list<Shape*>::iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
//       try{
//         return (*itr)->getShapeById(id);
//       }
//       catch(std::string e) {
//         if((*itr)->id() == id)
//           return (*itr);
//       }
//     }
//
//     // No match id
//     throw std::string("Expected get shape but shape not found");
//   }
//
//   std::string type() const {
//     return "Compound Shape";
//   }
// private:
//   std::list<Shape*>* m_shapes;
// };

#endif
