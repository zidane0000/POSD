#ifndef _SHAPE_ITERATOR_
#define _SHAPE_ITERATOR_

#include "shape.h"
#include "iterator.h"

template<class ForwardIterator>
class ShapeIterator : public Iterator {
public:
  ShapeIterator(ForwardIterator begin, ForwardIterator end):m_begin(begin), m_end(end) {
   // initialize iterator.
   first();
  }

  void first() {
      // initialize iterator.
      m_current = m_begin;
  }

  void next() {
      // move iterator to next position,
      // throw std::string "Moving past the end!" when iterator move over the range of the structure.
      if(isDone())
        throw std::string("Moving past the end!");
      else
        m_current++;
  }

  bool isDone() const {
      // return true when iterator reach the end of the structure.
      return m_current == m_end;
  }

  Shape* currentItem() const {
      // return the shape that iterator currently point at.
      return *m_current;
  }

private:
  ForwardIterator m_begin;
  ForwardIterator m_end;
  ForwardIterator m_current;
};

#endif
