#ifndef _ELLISPE_
#define _ELLISPE_

#include "shape.h"
#include "visitor.h"

class Ellipse: public Shape {
public:
  Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes): Shape(id) {
      // If the ellipse can't be successfully created,
      // handle the exception by throwing string "This is not a ellipse!"
      if(semiMajorAxes <= 0 || semiMinorAxes <= 0 || semiMajorAxes < semiMinorAxes){
        throw std::string("This is not an ellipse!");
        m_semiMajorAxes = 0;
        m_semiMinorAxes = 0;
      }
      else {
        m_semiMajorAxes = semiMajorAxes;
        m_semiMinorAxes = semiMinorAxes;
        // m_id = id;
        // m_color = "white";
      }
  }

  Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color): Shape(id, color) {
      // If the ellipse can't be successfully created,
      // handle the exception by throwing string "This is not a ellipse!"
      if(semiMajorAxes <= 0 || semiMinorAxes <= 0 || semiMajorAxes < semiMinorAxes){
        throw std::string("This is not an ellipse!");
        m_semiMajorAxes = 0;
        m_semiMinorAxes = 0;
      }
      else {
        m_semiMajorAxes = semiMajorAxes;
        m_semiMinorAxes = semiMinorAxes;
        // m_id = id;
        // m_color = color;
      }
  }

  Ellipse(double semiMajorAxes, double semiMinorAxes) : Ellipse("-1", semiMajorAxes, semiMinorAxes){}

  double area() const {
      // return the area of the Ellipse.
      int i_area = M_PI * m_semiMajorAxes * m_semiMinorAxes * 1000;
      return (double)i_area / 1000.0;
  }

  double perimeter() const {
      // return the perimeter of the Ellipse.
      //int i_perimeter = (2 * M_PI * m_semiMinorAxes + 4 * (m_semiMajorAxes - m_semiMinorAxes)) * 1000;
      //return (double)i_perimeter / 1000.0;
      //double d_perimeter = 2 * M_PI * m_semiMinorAxes + 4 * (m_semiMajorAxes - m_semiMinorAxes);
      //to3f_double(d_perimeter);
      //return d_perimeter;

      double d_perimeter = 2 * M_PI * m_semiMinorAxes + 4 * (m_semiMajorAxes - m_semiMinorAxes);
      return d_perimeter;
  }

  std::string info() const {
      // return the info of the Ellipse.
      // ex. Ellipse (3.712, 4.000)
      char c_info[50];
      sprintf(c_info, "Ellipse (%.3f, %.3f)", m_semiMajorAxes, m_semiMinorAxes);
      std::string s_info(c_info);
      return s_info;
  }

  std::string type() const {
    return "Ellipse";
  }

  void accept(Visitor* visitor) {
    visitor->visit(this);
  }

  double getSemiMajorAxes() const {
    return m_semiMajorAxes;
  }

  double getSemiMinorAxes() const {
    return m_semiMinorAxes;
  }

private:
  double m_semiMajorAxes, m_semiMinorAxes;
};

#endif
