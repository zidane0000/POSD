#include "shape.h"

#ifndef _SORT_
#define _SORT_

template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
  if (first != last) {
    RandomAccessIterator pivot = first;       // pivot
    RandomAccessIterator p_smaller = first;   // Index of smaller element
    RandomAccessIterator p_current = p_smaller + 1;
    while(p_current != last) {
      if(comp(*p_current, *pivot)) {
        p_smaller+=1;
        swap(*p_smaller, *p_current);
      }
      p_current+=1;
    }
    swap(*pivot, *p_smaller);
    if(first != p_smaller)
      quickSort(first, p_smaller, comp);  // Before pivot
    if(last != p_smaller)
      quickSort(p_smaller + 1, last, comp);   // After pivot
  }
}

bool areaAscendingCompare(Shape*a, Shape*b) { return a->area() < b->area(); };

bool areaDescendingCompare(Shape*a, Shape*b) { return a->area() > b->area(); };

bool perimeterAscendingCompare(Shape*a, Shape*b) { return a->perimeter() < b->perimeter(); };

bool perimeterDescendingCompare(Shape*a, Shape*b) { return a->perimeter() > b->perimeter(); };

class AscendingCompare{
public:
  AscendingCompare(std::string feature): _feature(feature) {}

  bool operator()(Shape* a, Shape* b) {
    if(_feature == "area")
      return a->area() < b->area();
    else if(_feature == "perimeter")
      return a->perimeter() < b->perimeter();
    else
      throw string("Unkown feature");
  }
private:
  std::string _feature;
};

class DescendingCompare{
public:
  DescendingCompare(std::string feature): _feature(feature) {}

  bool operator()(Shape* a, Shape* b) {
    if(_feature == "area")
      return a->area() > b->area();
    else if(_feature == "perimeter")
      return a->perimeter() > b->perimeter();
    else
      throw string("Unkown feature");
  }
private:
  std::string _feature;
};

#endif
