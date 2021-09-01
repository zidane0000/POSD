#include "shape.h"
#include "null_iterator.h"

Shape::Shape(std::string id):m_id(id), m_color("white"){} // interface for default color "white".

Shape::Shape(std::string id, std::string color):m_id(id), m_color(color){} // interface for color input by user.

std::string Shape::id() const { return m_id; } // return id of shape

std::string Shape::color() const { return m_color; } // return color of shape.

void Shape::addShape(Shape *shape) { throw std::string("Only compound shape can add shape!"); } // throw std::string "Only compound shape can add shape!"

void Shape::deleteShapeById(std::string id){ throw std::string("Only compound shape can delete shape!"); } // throw std::string "Only compound shape can delete shape!"

Shape* Shape::getShapeById(std::string id) const{ throw std::string("Only compound shape can get shape!"); } // throw std::string "Only compound shape can get shape!"

Iterator* Shape::createIterator() const { return new NullIterator; };

void Shape::setColor(std::string color) { m_color = color; }

Shape::~Shape(){};
