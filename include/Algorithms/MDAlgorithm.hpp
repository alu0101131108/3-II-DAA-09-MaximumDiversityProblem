#ifndef __MDALGORITHM_H__
#define __MDALGORITHM_H__
#include "./../PointSet.hpp"

const int LOWER_DISTANCE_LIMIT = -99999999;

class PointSet;
class MDAlgorithm
{
public:
  virtual PointSet run(PointSet set, int subsetSize) = 0;
};

#endif // __MDALGORITHM_H__