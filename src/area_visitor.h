#ifndef _AREA_VISITOR_
#define _AREA_VISITOR_

#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "visitor.h"

class AreaVisitor : public Visitor {
public:
  void visit(Ellipse* ellipse) {
      // caculate the area of Ellipse.
      // DO NOT use ellipse->area() to get area directly.
      // you may add public function for Ellipse to get it's data members.
      int i_area = M_PI * ellipse->getSemiMajorAxes() *ellipse->getSemiMinorAxes() * 1000;
      _result = (double)i_area / 1000.0;
  }

  void visit(Triangle* triangle) {
      // caculate the area of Triangle.
      // DO NOT use triangle->area() to get area directly.
      // you may add public function for Triangle to get it's data members.
      int i_area = ((triangle->getPoint2()->getX() - triangle->getPoint1()->getX()) * (triangle->getPoint3()->getY() - triangle->getPoint1()->getY())
       - (triangle->getPoint3()->getX() - triangle->getPoint1()->getX()) * (triangle->getPoint2()->getY() - triangle->getPoint1()->getY())) * 1000.0 / 2.0;
      double d_area = (double)i_area / 1000.0;
      _result = (d_area > 0.0) ? d_area : -d_area;
  }

  void visit(Rectangle* rectangle) {
      // caculate the area of Rectangle.
      // DO NOT use rectangle->area() to get area directly.
      // you may add public function for Rectangle to get it's data members.
      int  i_area = rectangle->getLength() * rectangle->getWidth() * 1000;
      _result = (double)i_area / 1000.0;
  }

  void visit(CompoundShape* compoundShape) {
      // caculate the area of CompoundShape.
      // DO NOT use compoundShape->area() to get area directly.
      // you may add public function for CompoundShape to get it's data members.
      double sum_area = 0.0;
      std::list<Shape*> m_shapes = compoundShape->getShapes();
      if(!m_shapes.empty()) {
        AreaVisitor av;
        for(std::list<Shape*>::const_iterator itr = m_shapes.begin(); itr !=  m_shapes.end(); itr++) {
          (*itr)->accept(&av);
          sum_area += av.area();
        }
      }
      _result = sum_area;
  }

  double area() const {
    // return area;
    return _result;
  }

private:
  double _result;
};

#endif
