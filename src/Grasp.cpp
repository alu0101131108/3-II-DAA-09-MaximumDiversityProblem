#include "./../include/Algorithms/Grasp.hpp"

Grasp::Grasp(int iterations_, int lrcSize_, int iterationsMode_) :
iterations(iterations_), lrcSize(lrcSize_), iterationsMode(iterationsMode_)
{}

PointSet Grasp::constructive(PointSet set, int subsetSize)
{
  PointSet MDSubset(set.getDimension()), candidates;
  Point farthest, random, gravityCenter = set.getGravityCenter();
  do
  {
    // Select lrcSize best points as candidates for given gravity center.
    for (int i = 0; i < lrcSize && set.getSize() > 0; i++)
    {
      farthest = set.getFarthestPointTo(gravityCenter);
      candidates.insert(farthest);
      set.extract(farthest);
    }

    // Perfom a random insertion among candidates and reinsert others.
    random = candidates[rand() % lrcSize];
    MDSubset.insert(random);
    candidates.extract(random);
    set.insert(candidates);
    
    // Recalculate gravity center and clear lrc;
    gravityCenter = MDSubset.getGravityCenter();
    candidates.clear();

  } while (MDSubset.getSize() != subsetSize);
  
  remainer = set;
  return MDSubset;
}

PointSet Grasp::update(PointSet set)
{
  PointSet previous, updated = set;
  Point extracted, bestExtracted, bestInserted;
  float diversity, bestDiversity;

  do
  {
    previous = updated;
    bestDiversity = previous.getDiversityValue();

    // Update solution.
    for (int i = 0; i < updated.getSize(); i++)
    {
      extracted = updated[0];
      updated.extract(updated[0]);
      for (int j = 0; j < remainer.getSize(); j++)
      {
        updated.insert(remainer[j]);

        // Keep track of best extraction/insertion.
        diversity = updated.getDiversityValue();
        if (diversity > bestDiversity)
        {
          bestDiversity = diversity;
          bestExtracted = extracted;
          bestInserted = remainer[j];
        }
        updated.extract(remainer[j]);
      }
      updated.insert(extracted);
    }

    // If found, perform best insertion/extraction.
    if (bestDiversity != updated.getDiversityValue())
    {
      updated.extract(bestExtracted);
      updated.insert(bestInserted);
    }

  } while (previous.getDiversityValue() != updated.getDiversityValue());

  return updated;
}

PointSet Grasp::run(PointSet set, int subsetSize)
{
  int iteration = 0;
  float diversity, bestDiversity = 0;
  PointSet MDSubset, bestMDSubset;
  bool noProgress;

  while (iteration < iterations)
  {
    noProgress = true;
    MDSubset = constructive(set, subsetSize);
    MDSubset = update(MDSubset);
    diversity = MDSubset.getDiversityValue();
    
    if (diversity > bestDiversity)
    {
      bestDiversity = diversity;
      bestMDSubset = MDSubset;
      noProgress = false;
    }

    switch (iterationsMode)
    {
      case ALL:
        iteration++;
        break;

      case NO_PROGRESS:
        if (noProgress)
          iteration++;
        break;

      default:
        std::cout << "ERROR: Unknown iterations type for Grasp.\n";
        throw 72;
    }
  }
  
  return bestMDSubset;
}