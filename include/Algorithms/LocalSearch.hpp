#ifndef __LOCALSEARCH_H__
#define __LOCALSEARCH_H__

#include "MDAlgorithm.hpp"
#include <vector>
#include <algorithm>

class LocalSearch : public MDAlgorithm
{
  PointSet run(PointSet set, int subsetSize);
};

#endif // __LOCALSEARCH_H__