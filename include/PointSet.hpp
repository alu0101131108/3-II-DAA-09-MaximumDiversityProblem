#ifndef __POINTSET_H__
#define __POINTSET_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "./Point.hpp"
#include "./Algorithms/MDAlgorithm.hpp"

class MDAlgorithm;
class PointSet
{
private:
  std::vector<Point> points;
  int dimension;
  MDAlgorithm* MDSubsetGenerator;

public:
  PointSet();
  PointSet(int dimension_, std::vector<Point> points_ = {});
  ~PointSet();
  void setMDSubsetGenerator(MDAlgorithm *MDSubsetGenerator_);
  void loadFromFile(std::string filename);
  void printPoints();
  PointSet generateMDSubset(int subsetSize);
  Point getGravityCenter();
  float getDiversityValue();
  int getDimension();
  int getSize();
  Point getFarthestPointTo(Point selected);
  PointSet substract(PointSet other);
  void insert(Point toInsert);
  void insert(PointSet toInsert);
  void pop();
  void popBack(int times = 1);
  void extract(Point toExtract);
  bool belongs(Point possible);
  void clear();
  std::string toString();

  Point &operator[](int index);
};



#endif // __POINTSET_H__