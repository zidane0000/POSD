#ifndef _SHAPE_BUILDER_
#define _SHAPE_BUILDER_

#include "shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "compound_shape.h"
#include <stack>
#include <deque>

class ShapeBuilder {
public:
  ShapeBuilder() {
    unuse_id = 0;
    std::stack<Shape *>().swap(m_stack);
    std::stack<bool>().swap(m_stack_compound);
  }

  void buildRectangle(double length, double width) {
    // build a rectangle with an unique id and push in a std::stack.
    m_stack.push(new Rectangle(std::to_string(unuse_id), length, width));
    unuse_id += 1;
  }

  void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
    // build a ellipse with an unique id and push in a std::stack.
    m_stack.push(new Ellipse(std::to_string(unuse_id), semiMajorAxes, semiMinorAxes));
    unuse_id += 1;
  }

  void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    // build a triangle with an unique id and push in a std::stack.
    m_stack.push(new Triangle(std::to_string(unuse_id), { new TwoDimensionalCoordinate(x1, y1), new TwoDimensionalCoordinate(x2, y2), new TwoDimensionalCoordinate(x3, y3) }));
    unuse_id += 1;
  }

  void buildCompoundShapeBegin() {
    // for notifing beginning of a Compound Shape.
    m_stack.push(new CompoundShape(std::to_string(unuse_id), {}));
    unuse_id += 1;
    m_stack_compound.push(false);
  }

  void buildCompoundShapeEnd() {
    // for notifing ending of a Compound Shape.
    std::list<Shape *> tmp;
    while((m_stack.top()->type() != "Compound Shape") || (m_stack.top()->type() == "Compound Shape" && m_stack_compound.top())) {
      tmp.push_back(m_stack.top());
      m_stack.pop();

      if(m_stack.top()->type() == "Compound Shape" && m_stack_compound.top())
        m_stack_compound.pop();
    }

    for(auto it = tmp.rbegin(); it!= tmp.rend(); it++)
      m_stack.top()->addShape(*it);

    m_stack_compound.pop();
    m_stack_compound.push(true);
  }

  std::deque<Shape*> getResult() {
    // return result.
    std::deque<Shape*> result;

    while(!m_stack.empty()) {
      result.push_back(m_stack.top());
      m_stack.pop();
    }

    return std::deque<Shape*>(result.rbegin(), result.rend());
  }

private:
  int unuse_id;
  std::stack<Shape *> m_stack;
  std::stack<bool> m_stack_compound;
};

#endif
