#include "./../include/Algorithms/LocalSearch.hpp"

PointSet LocalSearch::run(PointSet set, int subsetSize)
{
  // Constructive phase.
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

  // Update by local search phase.
  int remainerSize = set.getSize();
  float diversity, bestDiversity = MDSubset.getDiversityValue();
  Point extracted, bestExtracted, bestInserted;
  for (int i = 0; i < subsetSize; i++)
  {
    extracted = MDSubset[0];
    MDSubset.extract(MDSubset[0]);
    for (int j = 0; j < remainerSize; j++)
    {
      MDSubset.insert(set[j]);
      // Keep track of best extraction/insertion.
      diversity = MDSubset.getDiversityValue();
      if (diversity > bestDiversity)
      {
        bestDiversity = diversity;
        bestExtracted = extracted;
        bestInserted = set[j];
      }
      MDSubset.extract(set[j]);
    }
    MDSubset.insert(extracted);
  }

  // If found, perform best insertion/extraction.
  if (bestDiversity != MDSubset.getDiversityValue())
  {
    MDSubset.extract(bestExtracted);
    MDSubset.insert(bestInserted);
  }

  return MDSubset;
}
