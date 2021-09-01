#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "shape.h"
#include "visitor.h"

class Rectangle: public Shape {
public:
  Rectangle(std::string id, double length, double width): Shape(id) {
      // If the rectangle can't be successfully created,
      // handle the exception by throwing string "This is not a rectangle!"
      if(length <= 0 || width <= 0){
        throw std::string("This is not a rectangle!");
        m_length = 0;
        m_width = 0;
      }
      else {
        m_length = length;
        m_width = width;
        // m_id = id;
        // m_color = "white";
      }
  }

  Rectangle(std::string id, double length, double width, std::string color): Shape(id, color) {
      // If the rectangle can't be successfully created,
      // handle the exception by throwing string "This is not a rectangle!"
      if(length <= 0 || width <= 0){
        throw std::string("This is not a rectangle!");
        m_length = 0;
        m_width = 0;
      }
      else {
        m_length = length;
        m_width = width;
        // m_id = id;
        // m_color = color;
      }
  }

  Rectangle(double length, double width) : Rectangle("-1", length, width){}

  double area() const {
      // return the area of the Rectangle.
      int  i_area = m_length * m_width * 1000;
      return (double)i_area / 1000.0;
  }

  double perimeter() const {
      // return the perimeter of the Rectangle.
      int i_perimeter = (m_length + m_width) * 2 * 1000;
      return (double)i_perimeter / 1000.0;;
  }

  std::string info() const {
      // return the info of the Rectangle.
      // ex. Rectangle (3.712, 4.000)
      char c_info[50];
      sprintf(c_info, "Rectangle (%.3f, %.3f)", m_length, m_width);
      std::string s_info(c_info);
      return s_info;
  }

  std::string type() const {
    return "Rectangle";
  }

  void accept(Visitor* visitor) {
    visitor->visit(this);
  }

  double getLength() const {
    return m_length;
  }

  double getWidth() const {
    return m_width;
  }

private:
  double m_length = 0, m_width = 0;
};

#endif
