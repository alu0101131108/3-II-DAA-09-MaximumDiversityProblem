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
  void insert(Point toInsert);
  void extract(Point toExtract);
  bool belongs(Point possible);
};



#endif // __POINTSET_H__