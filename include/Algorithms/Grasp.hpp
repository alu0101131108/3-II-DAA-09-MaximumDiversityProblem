#ifndef __GRASP_H__
#define __GRASP_H__

#include "MDAlgorithm.hpp"
#include <vector>
#include <algorithm>

enum Iterations
{
  ALL,
  NO_PROGRESS
};

class Grasp : public MDAlgorithm
{
  private:
    int iterations;
    int lrcSize;
    int iterationsMode;
    PointSet originalSet;

    PointSet constructive(PointSet set, int subsetSize);
    PointSet update(PointSet set);

  public:
    Grasp(int iterations_, int lrcSize_, int iterationsMode_);
    PointSet run(PointSet set, int subsetSize);
};

#endif // __GRASP_H__