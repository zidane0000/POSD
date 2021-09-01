#ifndef _SHAPE_SETTER_
#define _SHAPE_SETTER_

#include "filter.h"

typedef void (*Setter)(Shape*);

class ShapeSetter : public Filter {
public:
  ShapeSetter(Setter set) : m_set(set) {
    nextFilter = nullptr;
  }
  // `Setter` is a template name for lambda,
  //  you may use your own name.

  Filter* setNext(Filter* filter) {
    // seeting next filter.
    if(nextFilter) {
      nextFilter->setNext(filter);
    }
    else {
      nextFilter = filter;
    }
    return this;
  }

  std::list<Shape*> push(std::list<Shape*> shapes) {
    // push down setted data and return result.
    for(Shape* shape : shapes)
      m_set(shape);

    if(nextFilter)
      shapes = nextFilter->push(shapes);

    return shapes;
  }

private:
  Setter m_set;
  Filter * nextFilter = nullptr;
};

#endif
