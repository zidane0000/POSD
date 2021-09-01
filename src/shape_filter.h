#ifndef _SHAPE_FILTER_
#define _SHAPE_FILTER_

#include "filter.h"

typedef bool Predicate(Shape*);

class ShapeFilter : public Filter {
public:
  ShapeFilter(Predicate pred):m_pred(pred) {
    nextFilter = nullptr;
  }
  // `Predicate` is a template name for lambda,
  //  you may use your own name.

  Filter* setNext(Filter* filter) {
    // setting next filter.
    if(nextFilter) {
      nextFilter->setNext(filter);
    }
    else {
      nextFilter = filter;
    }
    return this;
  }

  std::list<Shape*> push(std::list<Shape*> shapes) {
    // push down filtered data and return result.
    std::list<Shape*> res;
    for(Shape* shape : shapes)
      if(m_pred(shape))
        res.push_back(shape);

    if(nextFilter)
      res = nextFilter->push(res);

    return res;
  }

private:
  Predicate * m_pred;
  Filter * nextFilter;
};

#endif
