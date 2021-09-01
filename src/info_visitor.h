#ifndef _INFO_VISITOR_
#define _INFO_VISITOR_

#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "visitor.h"

class InfoVisitor : public Visitor {
public:
  void visit(Ellipse* ellipse) {
      // create info of ellipse, same way as ellipse->info().
      // DO NOT use ellipse->info() to get info directly.
      // you may add public function for Ellipse to get it's data members.
      char c_info[50];
      sprintf(c_info, "Ellipse (%.3f, %.3f)", ellipse->getSemiMajorAxes(), ellipse->getSemiMinorAxes());
      std::string s_info(c_info);
      _result = s_info;
  }

  void visit(Triangle* triangle) {
      // create info of ellipse, same way as triangle->info().
      // DO NOT use triangle->info() to get info directly.
      // you may add public function for Triangle to get it's data members.
      char c_info[80];
      sprintf(c_info, "Triangle ([%.3f, %.3f], [%.3f, %.3f], [%.3f, %.3f])"
      , triangle->getPoint1()->getX(), triangle->getPoint1()->getY()
      , triangle->getPoint2()->getX(), triangle->getPoint2()->getY()
      , triangle->getPoint3()->getX(), triangle->getPoint3()->getY());
      std::string s_info(c_info);
      _result = s_info;
  }

  void visit(Rectangle* rectangle) {
      // create info of rectangle, same way as rectangle->info().
      // DO NOT use rectangle->info() to get info directly.
      // you may add public function for Rectangle to get it's data members.
      char c_info[50];
      sprintf(c_info, "Rectangle (%.3f, %.3f)", rectangle->getLength(), rectangle->getWidth());
      std::string s_info(c_info);
      _result = s_info;
  }

  void visit(CompoundShape* compoundShape) {
      // create info of compoundShape, same way as compoundShape->info().
      // DO NOT use compoundShape->info() to get info directly.
      // you may add public function for CompoundShape to get it's data members.
      std::string sum_info = "Compound Shape {";
      std::list<Shape*> m_shapes = compoundShape->getShapes();
      if(!m_shapes.empty()) {
        InfoVisitor iv;
        for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
          (*itr)->accept(&iv);
          sum_info = sum_info + iv.info() + ", ";
        }
      }

      sum_info = sum_info.substr(0, sum_info.size() - 2);
      sum_info+= "}";
      _result = sum_info;
  }

  std::string info() const {
      // return info;
      return _result;
  }

private:
  std::string _result;
};

#endif
