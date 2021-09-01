#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "shape.h"
#include "two_dimensional_coordinate.h"
#include "visitor.h"

class Triangle: public Shape {
public:
  Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> vectors): Shape(id) {
      // If the triangle can't be successfully created,
      // handle the exception by throwing string "This is not a triangle!"
      if(vectors.size() != 3
        || ((vectors[0]->getX() == vectors[1]->getX()) && (vectors[0]->getY() == vectors[1]->getY()))
        || ((vectors[0]->getX() == vectors[2]->getX()) && (vectors[0]->getY() == vectors[2]->getY()))
        || ((vectors[1]->getX() == vectors[2]->getX()) && (vectors[1]->getY() == vectors[2]->getY()))){
        throw std::string("This is not a triangle!");
      }
      else{
        point_1 = vectors[0];
        point_2 = vectors[1];
        point_3 = vectors[2];
        // m_id = id;
        // m_color = "white";
      }
  }

  Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> vectors, std::string color): Shape(id, color) {
      // If the triangle can't be successfully created,
      // handle the exception by throwing string "This is not a triangle!"
      if(vectors.size() != 3
        || ((vectors[0]->getX() == vectors[1]->getX()) && (vectors[0]->getY() == vectors[1]->getY()))
        || ((vectors[0]->getX() == vectors[2]->getX()) && (vectors[0]->getY() == vectors[2]->getY()))
        || ((vectors[1]->getX() == vectors[2]->getX()) && (vectors[1]->getY() == vectors[2]->getY()))){
        throw std::string("This is not a triangle!");
      }
      else{
        point_1 = vectors[0];
        point_2 = vectors[1];
        point_3 = vectors[2];
        // m_id = id;
        // m_color = color;
      }
  }

  Triangle(std::vector<TwoDimensionalCoordinate*> vectors) : Triangle("-1", vectors) {}


  double area() const {
      // return the area of the Triangle.
      int i_area = ((point_2->getX() - point_1->getX()) * (point_3->getY() - point_1->getY())
       - (point_3->getX() - point_1->getX()) * (point_2->getY() - point_1->getY())) * 1000.0 / 2.0;
      double d_area = (double)i_area / 1000.0;
      return (d_area > 0.0) ? d_area : -d_area;
  }

  double perimeter() const {
      // return the perimeter of the Triangle.
      double len_01 = sqrt((point_2->getX() - point_1->getX()) * (point_2->getX() - point_1->getX())
       + (point_2->getY() - point_1->getY()) * (point_2->getY() - point_1->getY()));

      double len_02 = sqrt((point_3->getX() - point_1->getX()) * (point_3->getX() - point_1->getX())
       + (point_3->getY() - point_1->getY()) * (point_3->getY() - point_1->getY()));

      double len_12 = sqrt((point_2->getX() - point_3->getX()) * (point_2->getX() - point_3->getX())
       + (point_2->getY() - point_3->getY()) * (point_2->getY() - point_3->getY()));

      int i_perimeter = (len_01 + len_02 + len_12) * 1000;
      double d_perimeter = (double)i_perimeter / 1000.0;
      return d_perimeter;
  }

  std::string info() const {
      // return the info of the Triangle.
      // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
      char c_info[80];
      sprintf(c_info, "Triangle ([%.3f, %.3f], [%.3f, %.3f], [%.3f, %.3f])"
      , point_1->getX(), point_1->getY()
      , point_2->getX(), point_2->getY()
      , point_3->getX(), point_3->getY());
      std::string s_info(c_info);
      return s_info;
  }

  std::string type() const {
    return "Triangle";
  }

  void accept(Visitor* visitor) {
    visitor->visit(this);
  }

  TwoDimensionalCoordinate* getPoint1() const {
    return point_1;
  }

  TwoDimensionalCoordinate* getPoint2() const {
    return point_2;
  }

  TwoDimensionalCoordinate* getPoint3() const {
    return point_3;
  }

private:
  TwoDimensionalCoordinate* point_1;
  TwoDimensionalCoordinate* point_2;
  TwoDimensionalCoordinate* point_3;
};

#endif
