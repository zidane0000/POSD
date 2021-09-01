#ifndef _FILTER_
#define _FILTER_

#include "shape.h"

class Filter {
public:
  virtual Filter* setNext(Filter* filter) = 0;

  virtual std::list<Shape*> push(std::list<Shape*> shapes) = 0;
};

#endif
