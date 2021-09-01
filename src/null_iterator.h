#ifndef _NULL_ITERATOR_
#define _NULL_ITERATOR_

#include "iterator.h"

class NullIterator : public Iterator {
public:
  void first() { throw std::string("No child member!"); }

  void next() { throw std::string("No child member!"); }

  bool isDone() const { return true; }

  Shape* currentItem() const { throw std::string("No child member!"); }
};


#endif
