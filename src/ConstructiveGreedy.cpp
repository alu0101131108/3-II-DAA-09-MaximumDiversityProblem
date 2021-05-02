#include "./../include/Algorithms/ConstructiveGreedy.hpp"

PointSet ConstructiveGreedy::run(PointSet set, int subsetSize)
{
  PointSet MDSubset(set.getDimension());
  Point gravityCenter = set.getGravityCenter();
  Point farthest;
  do 
  {
    farthest = set.getFarthestPointTo(gravityCenter);
    MDSubset.insert(farthest);
    set.extract(farthest);
    gravityCenter = MDSubset.getGravityCenter();
  } while (MDSubset.getSize() != subsetSize);
  return MDSubset;
}
