#ifndef __POINT_H__
#define __POINT_H__

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include <cmath>

class Point
{
private:
  std::vector<float> coordinates;
  int dimension;

public:
  Point();
  Point(int dimension_, std::string stringCoordinates);
  Point(std::vector<float> coordinates_);
  ~Point();
  std::vector<float> getCoordinates();
  void setCoordinates(std::vector<float> coordinates_);
  void printCoordinates();
  float getDistanceTo(Point other);
  std::string toString();

  float & operator[](int dim);
  friend bool operator==(Point & left, Point & right);
};
#endif // __POINT_H__