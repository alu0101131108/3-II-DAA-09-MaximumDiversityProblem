#ifndef __CONSTRUCTIVEGREEDY_H__
#define __CONSTRUCTIVEGREEDY_H__
#include "MDAlgorithm.hpp"
#include <vector>
#include <algorithm>

class ConstructiveGreedy : public MDAlgorithm
{
  PointSet run(PointSet set, int subsetSize);
};
#endif // __CONSTRUCTIVEGREEDY_H__