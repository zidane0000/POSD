#ifndef _TWO_DIMENSIONAL_COORDINATE_
#define _TWO_DIMENSIONAL_COORDINATE_

#include "shape.h"

class TwoDimensionalCoordinate {
public:
  TwoDimensionalCoordinate(double x, double y){
    m_X = x;
    m_Y = y;
  }

  double getX() const{
      // return x;
    return m_X;
	}

	double getY() const{
		// return y;
    return m_Y;
	}
private:
  double m_X, m_Y;
};

#endif
